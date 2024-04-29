import string
import random
import csv

virus_codes = "abcdef"

def generate_random_dna(length):
    return ''.join(random.choice(virus_codes) for _ in range(length))

def generate_human_dna(virus, min_length=20, max_length=500):
    while True:
        human_dna = generate_random_dna(random.randint(min_length, max_length))
        if virus in human_dna or random.random() < 0.5:
            return human_dna

def main():
    files = []
    for i in range(1, 99):
        # Write to CSV file
        rows = 50
        file_name = f"test_data/input{i:02d}.csv"
        with open(file_name, "w", newline="") as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(["virus", "human"])
            for j in range(rows):
                virus_sequence = generate_random_dna(random.randint(5, 30))
                human_sequence = generate_human_dna(virus_sequence, 10 * i ** 2, 10 * i ** 3)
                writer.writerow([virus_sequence, human_sequence])
        files.append(file_name)
    print(file_name)

if __name__ == "__main__":
    main()
