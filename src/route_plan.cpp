#include "route_plan.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <unordered_map>
#include <queue>

// Custom hash function for coor (std::pair<double, double>)
namespace std {
    template <>
    struct hash<std::pair<double, double>> {
        size_t operator()(const std::pair<double, double>& p) const {
            auto h1 = std::hash<double>{}(p.first);
            auto h2 = std::hash<double>{}(p.second);
            return h1 ^ (h2 << 1); // Combine the two hash values
        }
    };
}

using namespace std;

void route_plan::load(QString file_path) {
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file";
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Invalid JSON format";
        return;
    }

    QJsonObject root = doc.object();
    QJsonArray features = root["features"].toArray();

    for (const QJsonValue &feature : features) {
        QJsonObject featureObj = feature.toObject();
        QJsonObject geometry = featureObj["geometry"].toObject();
        QJsonObject properties = featureObj["properties"].toObject();

        QString type = geometry["type"].toString();
        if (type == "Point") {
            QJsonArray coordinates = geometry["coordinates"].toArray();
            coor loct = {coordinates[0].toDouble(), coordinates[1].toDouble()};
            QString name = properties["name"].toString();
            QString desc = properties["description"].toString();
            places.emplace_back(loct, name, desc);
        } else if (type == "LineString") {
            QJsonArray coordinates = geometry["coordinates"].toArray();
            if (coordinates.size() < 2) continue;

            QJsonArray start = coordinates[0].toArray();
            QJsonArray end = coordinates[1].toArray();
            coor startCoor = {start[0].toDouble(), start[1].toDouble()};
            coor endCoor = {end[0].toDouble(), end[1].toDouble()};
            road_type rType = properties["description"].toString() == "自行车道" ? cycleway : sidewalk;
            double cong = properties["congestion"].toDouble();
            road r(startCoor, endCoor, rType, cong);
            r.setLength( calcu_length(r.getStart(), r.getEnd()) );
            roads.push_back(r);

        }
    }
}

void route_plan::create_graph() {

    unordered_map<coor, int> coor_to_id;
    for (int i = 0; i < places.size(); ++i) {
        coor_to_id[places[i].getLoct()] = i;
    }
    graph_d.resize(places.size());
    graph_t.resize(places.size());
    graph_m.resize(places.size());
    for (const auto &road : roads) {
        int start_id, end_id;
        auto it1 = coor_to_id.find(road.getStart());
        if (it1 == coor_to_id.end()) continue; 
        start_id = it1->second;
        auto it2 = coor_to_id.find(road.getEnd());
        if (it2 == coor_to_id.end()) continue; 
        end_id = it2->second;
        
        graph_d[start_id].emplace_back(end_id, road.getLength(), sidewalk);
        graph_d[end_id].emplace_back(start_id, road.getLength(), sidewalk);

        graph_t[start_id].emplace_back(end_id, road.getLength() / (1.3 * road.getCong()), sidewalk);
        graph_t[end_id].emplace_back(start_id, road.getLength() / (1.3 * road.getCong()), sidewalk);

        road_type type = road.getType();
        if(type == cycleway) {
            graph_m[start_id].emplace_back(end_id, road.getCong() * road.getLength() / (4.0 * road.getCong()), cycleway);
            graph_m[end_id].emplace_back(start_id, road.getCong() * road.getLength() / (4.0 * road.getCong()), cycleway);
        } else if (type == sidewalk) {
            graph_m[start_id].emplace_back(end_id, road.getCong() * road.getLength() / (1.3 * road.getCong()), sidewalk);
            graph_m[end_id].emplace_back(start_id, road.getCong() * road.getLength() / (1.3 * road.getCong()), sidewalk);
        }
    }
        
}

void route_plan::put_path() {
    vector<place_info> record;
    double dist = route_plan::shortest_path(12, {5,13,36,52,64,66}, graph_m, record);
    qDebug() << "最短用时:" << dist;
    qDebug() << "路径详情：";
    for (const auto &p : record) {
        qDebug() << "下一途径点：" << places[p.getId()].getName()<< "共用时：" << p.getWeight() 
        << "s 方式：" << (p.getType() == cycleway ? "自行车道" : "人行道") ;
    }
}


double route_plan::shortest_path(int start, const vector<int>& end, vector<vector<place_info>>& graph, vector<place_info>& record){
    const double INF = numeric_limits<double>::max();
    int cur = start;
    double all_dist = 0;
    vector<bool> visited(end.size(), false);
    for(int i = 0; i < end.size(); ++i) {
        vector<double> dist(graph.size(), INF);
        vector<place_info> prev(graph.size());
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

        dist[cur] = 0;
        pq.push({0, cur});
        int prior;
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            for(int j = 0; j < end.size(); ++j) {
                if (u == end[j] && !visited[j]) {
                    prior = cur;
                    cur = end[j];
                    visited[j] = true;
                    goto next;
                }
            }
                
            
            if (d > dist[u]) continue;
            for (const auto &neighbor : graph[u]) {
                int v = neighbor.getId();
                double weight = neighbor.getWeight();
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = place_info(u, weight, neighbor.getType());
                    
                    pq.push({dist[v], v});
                }
            }
        }
next:
        int next = cur;
        vector<place_info> temp;
        while(next != prior) {
            temp.emplace_back(next, all_dist + dist[next], prev[next].getType());
            next = prev[next].getId();
        }
        for(auto it = temp.rbegin(); it != temp.rend(); ++it){
            record.push_back(*it);
        }
        all_dist += dist[cur];
    }
    return all_dist;
}
