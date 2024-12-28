
void updateBook(){
    FILE *fileB = fopen(booksFile,"r");
    if(fileB == NULL){
        printf("echec douverture du fichier book.\n");
        return;
    }
    printf("veuillez rentrer lid du livre que vous voulez modifier:");
    int id;
    scanf("%d",id);
    FILE *ftemp = fopen("temp.txt","w");
    if(ftemp == NULL){
        printf("\nerreur lhors de louverture du fichier temporaraire pour update book.\n");
        return;
    }
    char ligne[150];
    int found =0;
    while(fgets(ligne,sizeof(ligne),fileB)){
        Book book; //book est un element de la structure Book
        sscanf(ligne,"%[^,],%[^,],%f,%d",&book.id,&book.title,&book.author,&book.price,&book.quantity);
        if(book.id == id){
           found=1;
           printf("veuillez entrez le nouveau titre du livre:");
           //getchar() Lit un seul caractère du flux input standard (stdin). elle consomme le carac de nouvelle ligne (\n)
           //qui reste dans le buffer d'entrée après la saisie 
           //d'un nombre par scanf() quon vas utilise dans price et quantity
           getchar();
           fgets(book.title,sizeof(book.title),stdin);
           //stdin: la ligne doit etre lue depuis le flux ENTREE standard le clavier.
           printf("\nveuillez entrez le nouveau auteur du livre:");
           getchar();
           fgets(book.author,sizeof(book.author),stdin);
           printf("\nveuillez entrez le nouveau prix du livre:");
           scanf("%f",&book.price);
           printf("\nveuillez entrez la quantite du livre:");
           scanf("%d",&book.quantity);
        }
        fprintf(ftemp, "%d,%s,%s,%f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }
    fclose(fileB);
    fclose(ftemp);
    remove(booksFile);
    rename("temp.txt",booksFile);
    if(found){
       // si found = 0 alors la conditions de if nest pas valable
         printf("livre trouve et modifier veuillez verfier avec loptien view.\n");
    }else{
     printf("livre non trouve vous vous etes tromper did peut etre reesayer.\n");
    }
}