import random as r

choices = ['keo', 'bua', 'bao']
history = []

def keo_bua_bao(person, computer):
    if person not in choices:
        return "Invalid selection!"

    if person == computer:
        return 0

    winning_cases = {
        'keo': 'bao',
        'bua': 'keo',
        'bao': 'bua'
    }

    if winning_cases[person] == computer:
        return 1
    else:
        return -1

point = {
    'nguoi': 0,
    'may': 0
}

while True:
    count = 1
    print(f"=== Game {count} ===")
    person = input("Person take (keo/bua/bao): ").strip().lower()

    if person == 'exit':
        print(f"=== Point of game ===")
        if point['nguoi'] > point['may']:
            print("Person win!")
        elif point['nguoi'] < point['may']:
            print("Computer win!")
        else:
            print("Draw!")
        break

    print("==== History play ====")
    for h in history:
        print(f" Ban ra: {h['person']} - May ra: {h['computer']}: Ket qua {h['result']}")


    computer = r.choice(choices)

    print(f"Person take {person}")
    print(f"Computer take {computer}")

    result = keo_bua_bao(person, computer)
    if result == 0:
        print("===> Draw!")
        point['nguoi'] += 0.5
        point['may'] += 0.5
    elif result == 1:
        print("===> Person win!")
        point['nguoi'] += 1
    else:
        print("===> Computer win!")
        point['may'] += 1
    history.append({
        'person': person,
        'computer': computer,
        'result': result,
    })
    count += 1
    print()