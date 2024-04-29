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
    # Write to CSV file
    rows = random.randint(50, 100)
    with open("test_data/input.csv", "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["virus", "human"])
        for i in range(rows):
            virus_sequence = generate_random_dna(random.randint(3, 40))
            human_sequence = generate_human_dna(virus_sequence, 1000, 10000)
            writer.writerow([virus_sequence, human_sequence])


    print("Data written to dna_sequences.csv")

if __name__ == "__main__":
    main()
