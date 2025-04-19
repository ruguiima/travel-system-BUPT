#include "route_plan.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <unordered_map>

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

void route_plan::load() {
    QFile file("./data/map_of_bupt.geojson");
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
            road_type rType = properties["description"].toString() == "自行车道" ? cycleway : path;
            double cong = properties["congestion"].toDouble();
            road r(startCoor, endCoor, rType, cong);
            r.calcu_leng();
            roads.push_back(r);

        }
    }
}

void road::calcu_leng() {
    const double degToRad = M_PI / 180.0;
    const double earthRadius = 6378137.0; 

    double dLat = (end.second - start.second) * degToRad;
    double dLon = (end.first - start.first) * degToRad;

    double meanLat = (end.second + start.second) / 2.0 * degToRad;
    double dx = dLon * earthRadius * cos(meanLat);
    double dy = dLat * earthRadius;

    length = sqrt(dx * dx + dy * dy);
}

void route_plan::create_graph() {
    unordered_map<coor, int> coor_to_id;
    for (int i = 0; i < places.size(); ++i) {
        coor_to_id[places[i].getLoct()] = i;
    }
    for (const auto &road : roads) {
        int start_id = coor_to_id[road.getStart()];
        int end_id = coor_to_id[road.getEnd()];
        
        graph_d[start_id].emplace_back(end_id, road.getLength(), path);
        graph_d[end_id].emplace_back(start_id, road.getLength(), path);

        graph_t[start_id].emplace_back(end_id, road.getCong() * road.getLength() / 1.3, path);
        graph_t[end_id].emplace_back(start_id, road.getCong() * road.getLength() / 1.3, path);

        road_type type = road.getType();
        if(type == cycleway) {
            graph_m[start_id].emplace_back(end_id, road.getCong() * road.getLength() / 4.0, cycleway);
            graph_m[end_id].emplace_back(start_id, road.getCong() * road.getLength() / 4.0, cycleway);
        } else if (type == path) {
            graph_m[start_id].emplace_back(end_id, road.getCong() * road.getLength() / 1.3, path);
            graph_m[end_id].emplace_back(start_id, road.getCong() * road.getLength() / 1.3, path);
        }
    }
        
}