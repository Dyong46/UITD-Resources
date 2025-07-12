import json
import random
from datetime import datetime, timezone

path_comments_content = {
    "Dental 3D": "comments-content/dental-3d.json",
    "Dental Clinic": "comments-content/dental-clinic.json",
    "Restaurant": "comments-content/restaurant.json",
    "Showroom": "comments-content/showroom.json",
    "STEM": "comments-content/stem.json",
    "Aesthetic clinic": "comments-content/aesthetic-clinic.json"
}

comments_content = {}
for key, path in path_comments_content.items():
    with open(path, 'r', encoding='utf-8') as f:
        comments_content[key] = json.load(f)

with open('accounts.json', 'r', encoding='utf-8') as f:
    account_data = json.load(f)
    account_ids = [acc['_id']['$oid'] for acc in account_data]

with open('videos.json', 'r', encoding='utf-8') as f:
    video_data = json.load(f)

# Time for createdAt/updatedAt
now_iso = datetime.now(timezone.utc).isoformat()

# Generate comments
generated_comments = []

for video in video_data:
    video_id = video['_id']['$oid']
    type_video = video['properties'].get('typeVideo', None)

    if not type_video or type_video not in comments_content:
        continue

    # random 5 to 30 comments
    num_comments = random.randint(5, 30)
    for _ in range(num_comments):
        comment = {
            "isDeleted": False,
            "accountId": {
                "$oid": random.choice(account_ids)
            },
            "videoId": {
                "$oid": video_id
            },
            "content": random.choice(comments_content[type_video]),
            "isEdited": False,
            "createdAt": {
                "$date": now_iso
            },
            "updatedAt": {
                "$date": now_iso
            },
            "__v": 0
        }
        generated_comments.append(comment)

with open('generated-comments-content.json', 'w', encoding='utf-8') as f:
    json.dump(generated_comments, f, ensure_ascii=False, indent=2)

print(f"✅ Đã tạo {len(generated_comments)} comments trong file 'generated-comments-content.json'")
