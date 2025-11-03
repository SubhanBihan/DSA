def main():
    import sys
    input = sys.stdin.readline

    n = int(input().strip())
    phonebook = {}

    for _ in range(n):
        parts = input().strip().split()
        cmd = parts[0]

        if cmd == "add":
            number, name = parts[1], parts[2]
            phonebook[number] = name  # add or overwrite
        elif cmd == "del":
            number = parts[1]
            phonebook.pop(number, None)  # safely remove if exists
        elif cmd == "find":
            number = parts[1]
            print(phonebook.get(number, "not found"))

if __name__ == "__main__":
    main()
