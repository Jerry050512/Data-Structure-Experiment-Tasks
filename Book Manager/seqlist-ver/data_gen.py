import random
import string
import csv

# Define functions to generate random data
def generate_isbn():
    isbn = ''.join(random.choices(string.digits, k=13))
    return isbn

def generate_book_name():
    adjectives = ['Powerful', 'Intriguing', 'Captivating', 'Thrilling', 'Inspiring']
    nouns = ['Adventure', 'Mystery', 'Romance', 'Fantasy', 'Biography']
    adj = random.choice(adjectives)
    noun = random.choice(nouns)
    book_name = f"{adj} {noun}"
    return book_name

def generate_author_name():
    first_names = ['Emma', 'Liam', 'Olivia', 'Noah', 'Ava', 'William']
    last_names = ['Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 'Davis']
    first_name = random.choice(first_names)
    last_name = random.choice(last_names)
    author_name = f"{first_name} {last_name}"
    return author_name

def generate_price():
    price = round(random.uniform(9.99, 29.99), 2)
    return price

def generate_data(num_records=50):
    # Generate random data
    num_records = num_records  # Number of records to generate
    data = []
    used_isbns = set()  # Set to store used ISBNs

    while len(data) < num_records:
        isbn = generate_isbn()
        if isbn in used_isbns:
            continue  # Skip if ISBN is already used
        used_isbns.add(isbn)
        book_name = generate_book_name()
        author_name = generate_author_name()
        price = generate_price()
        data.append([isbn, book_name, author_name, price])
    return data

data = generate_data(10)
for i in range(len(data)):
    data[i].insert(0, random.randint(1, 60))

# Write data to a CSV file
filename = 'new_book_data.csv'
with open(filename, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['ISBN', 'Book Name', 'Author Name', 'Price'])
    writer.writerows(data)

print(f"Random book data has been written to {filename}")