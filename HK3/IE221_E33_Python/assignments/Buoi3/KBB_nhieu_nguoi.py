import random as r

OPTIONS = ['keo', 'bua', 'bao']

WIN_RULES = {
    'keo': 'bao',
    'bua': 'keo',
    'bao': 'bua'
}


def determine_result(player, opponent):
    if player == opponent:
        return 0
    elif WIN_RULES[player] == opponent:
        return 1
    else:
        return -1


# --- Nhập thông tin người chơi ---
players = []
num_players = int(input("Số người chơi (không tính máy): "))
for i in range(num_players):
    name = input(f"Tên người chơi {i + 1}: ").strip()
    players.append(name)

players.append("Máy")  # Thêm máy vào danh sách người chơi

# --- Khởi tạo điểm số và lịch sử ---
scores = {name: 0 for name in players}
history = []
round_number = 1

print("\n=== BẮT ĐẦU TRÒ CHƠI KÉO – BÚA – BAO NHIỀU NGƯỜI ===\n")

while True:
    print(f"\n--- Round {round_number} ---")

    choices = {}
    someone_quit = False

    # Nhập lượt chơi của từng người
    for name in players:
        if name == "Máy":
            choices[name] = r.choice(OPTIONS)
        else:
            choice = input(f"{name} chọn (keo/bua/bao hoặc 'exit' để thoát): ").strip().lower()
            if choice == 'exit':
                someone_quit = True
                break
            while choice not in OPTIONS:
                print("⚠️ Lựa chọn không hợp lệ.")
                choice = input(f"{name} chọn lại (keo/bua/bao): ").strip().lower()
            choices[name] = choice

    if someone_quit:
        print("\n=== GAME KẾT THÚC ===")
        break

    print("\n--- Kết quả vòng này ---")
    for name, choice in choices.items():
        print(f"{name} chọn: {choice}")

    # Tính kết quả mỗi người với máy
    for name in players:
        if name == "Máy":
            continue
        result = determine_result(choices[name], choices["Máy"])
        if result == 1:
            scores[name] += 1
            print(f"✅ {name} thắng Máy!")
        elif result == -1:
            scores["Máy"] += 1
            print(f"❌ Máy thắng {name}")
        else:
            scores[name] += 0.5
            scores["Máy"] += 0.5
            print(f"🤝 {name} hòa Máy")

        # Ghi lại lịch sử mỗi người đấu với máy
        history.append({
            'round': round_number,
            'player': name,
            'player_choice': choices[name],
            'computer_choice': choices["Máy"],
            'result': result
        })

    round_number += 1

# --- Tổng kết ---
print("\n=== BẢNG TỔNG KẾT ĐIỂM ===")
for name, point in scores.items():
    print(f"{name}: {point} điểm")

# --- Hiển thị lịch sử ---
print("\n=== LỊCH SỬ CÁC VÒNG CHƠI ===")
for h in history:
    res_text = {
        1: f"{h['player']} thắng",
        -1: "Máy thắng",
        0: "Hòa"
    }[h['result']]
    print(f"Round {h['round']}: {h['player']} ({h['player_choice']}) vs Máy ({h['computer_choice']}) => {res_text}")
