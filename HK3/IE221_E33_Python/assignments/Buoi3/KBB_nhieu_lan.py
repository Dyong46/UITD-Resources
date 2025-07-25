import random as r

OPTIONS = ['keo', 'bua', 'bao']

WIN_RULES = {
    'keo': 'bao',
    'bua': 'keo',
    'bao': 'bua'
}


def determine_result(user, computer):
    if user == computer:
        return 0
    elif WIN_RULES[user] == computer:
        return 1
    else:
        return -1


# Start game
print("=== CHÀO MỪNG ĐẾN VỚI TRÒ CHƠI KÉO – BÚA – BAO ===")
print("Nhập 'keo', 'bua', hoặc 'bao' để chơi. Gõ 'exit' để thoát.\n")

score = {'user': 0, 'computer': 0}
round_number = 1
history = []

while True:
    print(f"\n--- Round {round_number} ---")
    user_choice = input("Bạn chọn (keo/bua/bao): ").strip().lower()

    if user_choice == 'exit':
        print("\n=== KẾT THÚC GAME ===")
        print(f"🔥 Tổng điểm - Bạn: {score['user']} | Máy: {score['computer']}")
        if score['user'] > score['computer']:
            print("Bạn là người chiến thắng!")
        elif score['user'] < score['computer']:
            print("Máy tính thắng!")
        else:
            print("Trận đấu hòa!")

        print("\n=== LỊCH SỬ CÁC VÒNG CHƠI ===")
        for h in history:
            result_text = {
                1: "Người thắng",
                -1: "Máy thắng",
                0: "Hòa"
            }[h['result']]
            print(f"Round {h['round']}: Bạn: {h['user']} - Máy: {h['computer']} => {result_text}")
        break

    if user_choice not in OPTIONS:
        print("⚠️ Lựa chọn không hợp lệ. Vui lòng chọn keo, bua hoặc bao.")
        continue

    computer_choice = r.choice(OPTIONS)
    print(f"Máy chọn: {computer_choice}")

    result = determine_result(user_choice, computer_choice)

    if result == 0:
        print("Hòa!")
    elif result == 1:
        print("Bạn thắng vòng này!")
        score['user'] += 1
    else:
        print("Máy thắng vòng này!")
        score['computer'] += 1

    history.append({
        'round': round_number,
        'user': user_choice,
        'computer': computer_choice,
        'result': result
    })

    round_number += 1
