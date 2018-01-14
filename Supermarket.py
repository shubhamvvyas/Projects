def supermarket(Items):
    n = len(Items)
    Items = sorted(Items, key=lambda x: (x[1], x[0]))
    a, b = Items[n-1]
    profit = a
    for i in range(1, n):
        a, b = Items[i]
        c, d = Items[i-1]
        if(b == d):
            continue
        profit = profit + c
    return profit