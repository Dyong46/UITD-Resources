
def ham(**kwargs):
    """"""
    print(kwargs)
    print(type(kwargs))
    print(kwargs.get('a'))

def f(**kwargs):
    """"""
    y = 0
    for key, value in kwargs.items():
        if key == 'a':
            y += value
        elif key == 'b':
            y += value ** 2
        elif key == 'c':
            y += value ** 3
        else:
            return None
    return y


if __name__ == "__main__":

    f(a=2, b=3) #y = 2X + 3
    f(a=2, b=3, c=4) # y = 2X^2 + 3X + 4
    f(a=2, b=3, c=4, d=5) #None

    # ham()
    # ham(a=1, b=2, c=3)
    # ham(a=5)
    # ham(b=10, c=100)

