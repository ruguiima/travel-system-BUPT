import json
import random

# 加载原始 GeoJSON 文件
with open('map_of_bupt.geojson', 'r', encoding='utf-8') as f:
    data = json.load(f)

# 遍历 features，替换 congestion 值
for feature in data['features']:
    if 'properties' in feature and 'congestion' in feature['properties']:
        feature['properties']['congestion'] = round(random.uniform(0.5, 1), 2)

# 保存为新文件
with open('map_of_bupt.geojson', 'w', encoding='utf-8') as f:
    f.write('{"type":"FeatureCollection","features":[\n')
    for i, feature in enumerate(data['features']):
        line = json.dumps(feature, ensure_ascii=False, separators=(',', ':'))
        f.write(line)
        if i < len(data['features']) - 1:
            f.write(',\n')
        else:
            f.write('\n')
    f.write(']}')
