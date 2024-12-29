void deleteBook() {
    int id;
    printf("Entrez ID du livre a supprimer : ");
    scanf("%d", &id);

    FILE *file = fopen(booksFile, "r");
    if (file == NULL) {
        printf("Aucun livre trouve.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf(" Impossible de creer un fichier temporaire.\n");
        fclose(file);
        return;
    }

    char ligne[150];
    int found = 0;
    while (fgets(ligne, sizeof(ligne), file)) {
        Book book;
        sscanf(ligne, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);

        if (book.id == id) {
            found = 1;
            continue; // Ne pas écrire ce livre dans le fichier temporaire
        }

        fprintf(temp, "%d,%s,%s,%.2f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }

    fclose(file);
    fclose(temp);

    remove(booksFile);
    rename("temp.txt", booksFile);

    if (found) {
        printf("Livre supprime avec succes.\n");
    } else {
        printf("Livre non trouve.\n");
    }
}
