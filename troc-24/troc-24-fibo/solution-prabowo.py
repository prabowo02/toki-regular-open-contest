REGS = {i for i in range(10, 100)}
def alloc_temp_regs(num):
    def _alloc_temp_regs(_func):
        def func(*args, **kwargs):
            regs = [REGS.pop() for _ in range(num)]
            _func(*args, regs=regs, **kwargs)
            for reg in regs:
                REGS.add(reg)
        return func
    return _alloc_temp_regs


ops = []

def _print(a):
    ops.append('. {}'.format(a))

def _and(a, b, c):
    ops.append('{} = {} & {}'.format(a, b, c))

def _or(a, b, c):
    ops.append('{} = {} | {}'.format(a, b, c))

def _xor(a, b, c):
    ops.append('{} = {} ^ {}'.format(a, b, c))

def _not(a, b):
    ops.append('{} = ~{}'.format(a, b))

def _lshift(a, b, d):
    ops.append('{} = {} << {}'.format(a, b, d))

def _rshift(a, b, d):
    ops.append('{} = {} >> {}'.format(a, b, d))


# Replace '011' with '100'
@alloc_temp_regs(4)
def _zeckendorf(a, b, regs=None):
    t1, t2, t3, t4 = regs

    # t3: '100' for every '011' in a; '0' otherwise
    _lshift(t1, b, 1)
    _lshift(t2, b, 2)
    _not(t3, b)
    _and(t3, t3, t1)
    _and(t3, t3, t2)

    # t4: '111' for every '100' in t3; '0' otherwise
    _rshift(t2, t3, 1)
    _rshift(t1, t3, 2)
    _or(t4, t2, t1)
    _or(t4, t4, t3)

    _xor(b, a, t4)


@alloc_temp_regs(14)
def _add(a, b, c, regs=None):
    t1, t2, t3, zero = regs[:4]
    shifts = regs[4:14]

    _not(t1, zero)
    _and(zero, t1, zero)
    
    # shifts[0] = 1
    _not(shifts[0], zero)
    _rshift(shifts[0], shifts[0], 31)
    for i in range(1, 10):
        _lshift(shifts[i], shifts[0], i)

    _or(a, b, b)

    for i in range(10)[::-1]:
        _zeckendorf(a, a)
        _and(t1, c, shifts[i])

        for j in range(i, -1, -2):
            _and(t2, t1, a)
            _xor(a, a, t2)
            _xor(t1, t1, t2)
            _lshift(t3, t2, 1)
            _xor(t1, t1, t3)

            if j == 1:
                _rshift(t3, t2, 1)
                _xor(t1, t1, t3)
            elif j > 1:
                _rshift(t3, t2, 2)
                _xor(t1, t1, t3)

        _xor(a, t1, a)


if __name__ == '__main__':
    _add(2, 0, 1)
    print(len(ops))
    print(*ops, sep='\n')
