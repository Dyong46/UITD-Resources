import json

# Đọc file videos.json
with open('videos.json', 'r', encoding='utf-8') as f:
    videos = json.load(f)

type_videos = set()

for video in videos:
    type_video = video.get('properties', {}).get('typeVideo')
    if type_video:
        type_videos.add(type_video)

print("📺 Type videos:")
for t in sorted(type_videos):
    print(f"- {t}")
