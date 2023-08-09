#include <stdio.h>

#define ROWS 10
#define SEATS_PER_ROW 10

// Function to display the seating arrangement
void displaySeats(char seats[][SEATS_PER_ROW]) {
    printf("Seating arrangement:\n");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            printf("%c ", seats[i][j]);
        }
        printf("\n");
    }
}

// Function to book a ticket
void bookTicket(char seats[][SEATS_PER_ROW], int row, int seat) {
    if (row < 1 || row > ROWS || seat < 1 || seat > SEATS_PER_ROW) {
        printf("Invalid row or seat number.\n");
        return;
    }

    if (seats[row - 1][seat - 1] == 'X') {
        printf("Seat already booked. Please choose another seat.\n");
        return;
    }

    seats[row - 1][seat - 1] = 'X';
    printf("Ticket booked successfully for Row %d Seat %d.\n", row, seat);
}

// Function to save booking information to a file
void saveBookingToFile(char seats[][SEATS_PER_ROW]) {
    FILE* file = fopen("seatbooking.txt", "w");

    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            fputc(seats[i][j], file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

// Function to load booking information from a file
void loadBookingFromFile(char seats[][SEATS_PER_ROW]) {
    FILE* file = fopen("booking.txt", "r");

    if (file == NULL) {
        // If the file does not exist, initialize all seats as available
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < SEATS_PER_ROW; j++) {
                seats[i][j] = 'O';
            }
        }
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            int c = fgetc(file);
            if (c != EOF && c != '\n') {
                seats[i][j] = (char)c;
            }
        }
    }

    fclose(file);
}

int main() {
    char seats[ROWS][SEATS_PER_ROW];
    loadBookingFromFile(seats);

    int choice, row, seat;

    do {
        printf("\nMenu:\n");
        printf("1. Display available seats\n");
        printf("2. Book a ticket\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats(seats);
                break;
            case 2:
                printf("Enter the row number: ");
                scanf("%d", &row);
                printf("Enter the seat number: ");
                scanf("%d", &seat);
                bookTicket(seats, row, seat);
                break;
            case 3:
                saveBookingToFile(seats);
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 3);

    return 0;
}
