
def ham(a, b=1, *args, **kwargs):
    """"""
    print('a =', a)
    print('b =', b)
    print('args =', args)
    print('kwargs =', kwargs)

if __name__ == "__main__":
    ham(1)
    ham(1, 2)
    ham(a, b=2, 7, 8, 9, c=7)