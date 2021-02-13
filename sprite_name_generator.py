
names = ["DOG", "GUARD", "OFFICER", "SS", "MUTANT"]

states = 4
directions = 8
dies = 3


def print_all():
    for name in names:
        for direction in range(1, directions+1):
            print(f"{name}_STATIC_{direction}", end=",")
            if (direction == 4):
                print()
        print("\n")
        for state in range(1, states + 1):
            for direction in range(1, directions + 1):
                print(f"{name}_WALK{state}_{direction}", end=",")
                if (direction == 4):
                    print()
            print("\n")
        for die in range(1, dies + 1):
            print(f"{name}_DIE_{die}", end=",")
        print(f"{name}_DEAD", end=",")
        print("\n")


print_all()
