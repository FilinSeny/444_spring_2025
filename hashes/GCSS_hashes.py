




def check(s1, s2, m, p = 3, M = 1e9+7, big_p = (3**10) % 1e9+7):
    hashes = set()
    for i in range(0, len(s1) - m):
        hashes.add((((s1[i + m] - s1[i] * (p**m))) % M)) #h(s[i +  m]) * p^i
        print(((s1[i + m] - s1[i] * (p**m)) % M))
    print(hashes)
    print("|----|", m)
    for i in range(0, len(s2) - m):
        if (((s2[i + m] - s2[i] * (p**m)) % M)) in hashes:
            return True
        print(((s2[i + m] - s2[i] * (p**m)) % M))
        
    return False
    


def count_hash(s1, p = 3, M = 1e9+7):
    res = [0]*(len(s1) + 1)
    #print(len(res))
    H = 0
    for i in range(0, len(s1)):
        H *= p
        H += ord(s1[i]) - ord("a") + 1
        print(H)
        H %= M 
        res[i + 1] = H

    return res



s1 = input()
s2 = input()


s1 = count_hash(s1)
s2 = count_hash(s2)



print('-------')


l = 0
r = min(len(s1) + 1, len(s2) + 1)

while (r - l > 1):
    m = (l + r) // 2
    if (check(s1, s2, m)):
        l = m
    else:
        r = m
    print(m, (check(s1, s2, m)))

print(l)