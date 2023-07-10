freqs = {}

with open("big.txt") as f:
    for line in f.readlines():
        line = ''.join(letter.lower() for letter in line if (letter.isalpha() or letter == ' '))

        words = line.split()

        for word in words:
            if not freqs.get(word):
                freqs[word] = 1
            else:
                freqs[word] += 1

with open("freqs.txt", 'w') as f:
    for key, item in freqs.items():
        if len(key) < 25:
            f.write(key + "\n")
