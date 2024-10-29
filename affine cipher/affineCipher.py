def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return None

def affine_decrypt(ciphertext, a, b, m):
    a_inv = mod_inverse(a, m)
    if a_inv is None:
        return None  
    plaintext = []
    for char in ciphertext:
        if char.isalpha():
            y = ord(char) - ord('a')  
            x = (a_inv * (y - b)) % m
            plaintext.append(chr(x + ord('a')))  
        else:
            plaintext.append(char)  
    return ''.join(plaintext)

def affine_brute_force(ciphertext):
    m = 26  
    possible_keys = [(a, b) for a in range(1, m) if gcd(a, m) == 1 for b in range(m)]
    
    results = []
    
    for a, b in possible_keys:
        decrypted_message = affine_decrypt(ciphertext, a, b, m)
        results.append((a, b, decrypted_message))
    
    return results

ciphertext = "opawaiamfsm"
results = affine_brute_force(ciphertext)

for a, b, plaintext in results:
    print(f"a={a}, b={b} -> Decrypted: {plaintext}")

