#include <iostream>
#include <string>
using namespace std;

struct Movies{
    string name_movie;
    int year_released;
    string genre;
    int length;
    struct Users;
    Movies *next;
};

struct Users{
    string mail;
    int age;
    string country;
    Users *next;
};

void menu_movie();
void insert_movie(Movies *&, string, int, string, int);
void show_movies(Movies *);
void delete_a_movie(Movies *&, string);
void menu_user();
void insert_user(Users *&, string, int, string);
void show_users(Users *);
void delete_a_user(Users *&, string);

Movies *Movie = NULL;
Users *User = NULL;

int main(){
    int option;
    do{
        cout<<"\n\tMENU\n";
        cout<<"1. Peliculas\n";
        cout<<"2. Series\n";
        cout<<"3. Usuarios\n";
        cout<<"4. Salir\n";
        cout<<"\n";
        cin>>option;

        switch(option){
            case 1: menu_movie();
                    break;

            case 2: cout<<"Mostrando las peliculas agregadas\n";
                    cout<<"\n";
                    show_movies(Movie);
                    break;

            case 3: menu_user();
                    break;
        }
    }while(option!=4);
}

//Parte de peliculas

void menu_movie(){
    int option, year, length;
    string name, genre;
    cout<<"1. Agregar pelicula\n";
    cout<<"2. Mostrar peliculas\n";
    cout<<"3. Eliminar una pelicula\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba la pelicula que desee agregar\n";
                getline(cin,name);
                cout<<"Año de lanzamiento\n";
                cin>>year;
                cin.ignore(1000,'\n');
                cout<<"Genero de la pelicula\n";
                getline(cin,genre);
                cout<<"Duracion de la pelicula (minutos)\n";
                cin>>length;
                insert_movie(Movie, name, year, genre, length);
                break;

        case 2: show_movies(Movie);
                break;

        case 3: cout<<"Escriba la pelicula que desee eliminar\n";
                getline(cin,name);
                delete_a_movie(Movie,name);
                break;

    }
}

void insert_movie(Movies *&Movie, string n, int yr, string g, int l){
    Movies *new_movie = new Movies;
    new_movie -> name_movie = n;
    new_movie -> year_released = yr;
    new_movie -> genre = g;
    new_movie -> length = l;
    Movies *aux1 = Movie;
    Movies *aux2;

    while(aux1 != NULL){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }

    if(Movie == aux1){
        Movie = new_movie;
    }
    else{
        aux2 -> next = new_movie;
    }
    new_movie -> next = aux1;
}

void show_movies(Movies *Movie){
    Movies *aux1 = Movie;
    while(aux1 != NULL){
        cout<<aux1 -> name_movie<<"\n";
        cout<<aux1 -> year_released<<"\n";
        cout<<aux1 -> genre<<"\n";
        cout<<aux1 -> length<<"\n";
        cout<<"\n";
        aux1 = aux1 -> next;
    }
}

void delete_a_movie(Movies *&Movie, string n){
    if (Movie!=NULL){
        Movies *aux1 = Movie;
        Movies *aux2 = NULL;

        while((aux1!=NULL)&&(aux1->name_movie!=n)){
            aux2=aux1;
            aux1=aux1->next;
        }
        
        if(aux1==NULL){
            cout<<"El elemento no se ha encontrado\n";
            cout<<"\n";
        }
        else if(Movie==aux1){
            Movie=Movie->next;
            delete aux1;
        }
        else{
            aux2->next=aux1->next;
            delete aux1;
            cout<<"Eliminado exitosamente\n";
            cout<<"\n";
        }
    }
}

//Parte Usuarios

void menu_user(){
    int option, age;
    string mail, country;
    cout<<"1. Agregar usuario\n";
    cout<<"2. Mostrar usuario\n";
    cout<<"3. Eliminar un usuario\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba su mail\n";
                getline(cin,mail);
                cout<<"Escriba su edad\n";
                cin>>age;
                cin.ignore(1000,'\n');
                cout<<"Genero de la pelicula\n";
                getline(cin,country);
                insert_user(User, mail, age, country);
                break;

        case 2: show_users(User);
                break;

        case 3: cout<<"Escriba la pelicula que desee eliminar\n";
                getline(cin,mail);
                delete_a_user(User,mail);
                break;

    }
}

void insert_user(Users *&Movie, string m, int a, string c){
    Users *new_movie = new Users;
    new_movie -> mail = m;
    new_movie -> age = a;
    new_movie -> country = c;
    Users *aux1 = User;
    Users *aux2;

    while(aux1 != NULL){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }

    if(Movie == aux1){
        Movie = new_movie;
    }
    else{
        aux2 -> next = new_movie;
    }
    new_movie -> next = aux1;
}

void show_users(Users *User){
    Users *aux1 = User;
    while(aux1 != NULL){
        cout<<aux1 -> mail<<"\n";
        cout<<aux1 -> age<<"\n";
        cout<<aux1 -> country<<"\n";
        cout<<"\n";
        aux1 = aux1 -> next;
    }
}

void delete_a_user(Users *&User, string m){
    if (User!=NULL){
        Users *aux1 = User;
        Users *aux2 = NULL;

        while((aux1!=NULL)&&(aux1->mail!=m)){
            aux2=aux1;
            aux1=aux1->next;
        }
        
        if(aux1==NULL){
            cout<<"El elemento no se ha encontrado\n";
            cout<<"\n";
        }
        else if(User==aux1){
            User=User->next;
            delete aux1;
        }
        else{
            aux2->next=aux1->next;
            delete aux1;
            cout<<"Eliminado exitosamente\n";
            cout<<"\n";
        }
    }
}
//Hola
