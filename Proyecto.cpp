#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
/*UCAB CODIGO REALIZADO POR:
Carmelo Moschella 30861195
Sebastián Figueira 30514220
Mouriss Eljawich 30773755
*/
struct Movies{
    string name_movie;
    int year_released;
    string genre;
    int length;
    Movies *next;
};

struct Users{
    string mail;
    int age;
    string country;
    string name;
    float score;
    Users *next;
    Users *qualifications_movies;
    Users *qualifications_series;
};

struct Series{
    string name_serie;
    int year_released;
    string genre;
    Series *next;
    Series *seasons;
    string name_season;
    Series *chapters;
    string name_chapter;
    int lenght;
    int chapter_number;
};

void menu_movie();
void insert_movie(Movies *&, string, int, string, int);
void show_movies(Movies *);
void delete_a_movie(Movies *&, string);
bool buscar_movie(Movies *,string);
void menu_user();
void insert_user(Users *&, string, int, string);
void show_users(Users *);
void delete_a_user(Users *&, string);
void menu_qualification_movie();
void add_qualification_movie(Users *&, string, string, float);
void show_qualification_movie(Users *, string);
void delete_a_qualification_movie(Users *&, string , string);
void top_5_qualifications_movies(Users *User);
void menu_qualification_serie();
void add_qualification_serie(Users *&, string, string, float);
void show_qualification_serie(Users *, string);
void delete_a_qualification_serie(Users *&, string , string);
void top_5_qualifications_series(Users *User);
bool buscar_user(Users *,string);
void menu_series_general();
void menu_series();
void insert_series(Series *&, string, int, string);
void show_series(Series *);
void delete_a_serie(Series *&, string);
void menu_seasons();
void insert_seasons(Series *&, string, int, string);
void show_seasons(Series *, string);
void delete_a_season(Series *&, string, string);
void menu_chapters();
void insert_chapters(Series *&, string, int, int, int, string, string);
void show_chapters(Series *, string, string);
void delete_a_chapter(Series *&, string , string, string);
bool buscar_serie(Series *, string);
bool buscar_season(Series *, string, string);
void leerPeliculas(const std::string& nombreArchivo, Movies*&);
void leerUsuarios(const std::string& nombreArchivo, Users *&);
void guardarPeliculasEnArchivo(Movies* Movie, const std::string& nombreArchivo);
void guardarUsuariosEnArchivo(Users* User, const std::string& nombreArchivo);
Movies *Movie = NULL;
Users *User = NULL;
Series *Serie = NULL;

// guardado de datos (no mover de aca o da error)(hasta donde yo probe)

void guardarPeliculasEnArchivo(Movies* Movie, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return;
    }

    Movies* aux = Movie;
    while (aux != NULL) {
        archivo << aux->name_movie << "," << aux->year_released << "," << aux->genre << ","
                << aux->length << "\n";
        aux = aux->next;
    }

    archivo.close();
    std::cout << "Películas guardadas exitosamente en " << nombreArchivo << std::endl;
}
void guardarUsuariosEnArchivo(Users* user, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return;
    }

    Users* aux = user;
    while (aux != NULL) {
        archivo << aux->mail << "," << aux->age << "," << aux->country << std::endl;
        aux = aux->next;
    }

    archivo.close();
    std::cout << "Usuarios guardados en " << nombreArchivo << " exitosamente." << std::endl;
}

int main(){
    std::string nombreArchivo = "Peliculas.txt"; 
    leerPeliculas(nombreArchivo, Movie);
    std::string nombreArchivo2 = "Usuarios.txt";
    leerUsuarios(nombreArchivo2, User);
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

            case 2: menu_series_general();
                    break;

            case 3: menu_user();
                    break;

            case 4: cout<<"Saliendo del programa\n";
                    guardarUsuariosEnArchivo(User, nombreArchivo2);
                    guardarPeliculasEnArchivo(Movie, nombreArchivo);
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
                cout<<"escriba su año de lanzamiento\n";
                cin>>year;
            //manejo de errores y verificacion d datos.
                if (year < 1888 || year > 2024) {
                    cout << "Año invalido. Introduzca un año entre 1888 y 2024.\n";
                    return;
                }
                cin.ignore(1000,'\n');
                cout<<"escriba el genero de la pelicula\n";
                getline(cin,genre);
                cout<<"Duracion de la pelicula (minutos)\n";
                cin>>length;
                    //manejo de errores y verificacion d datos. mael
                    if (length <= 0) {
                        cout << "Longitud no válida. Por favor ingrese una longitud positiva.\n";
                        return;
                    }
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
//lectura de archivos
void leerPeliculas(const std::string& nombreArchivo, Movies *&Movie) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    int yr; int duracion; string nombre; string genero; 
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        Movies pelicula;
        std::getline(iss, nombre, ',');
        iss >> yr;
        iss.ignore(); 
        std::getline(iss, genero, ',');
        iss >> duracion;
        iss.ignore();
        insert_movie(Movie, nombre, yr, genero, duracion);
    }
    archivo.close();
}
void leerUsuarios(const std::string& nombreArchivo, Users*& User){
    std::ifstream archivo(nombreArchivo);    
    std::string linea;
    int edad; string mail; string pais;
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }
    while (std::getline(archivo, linea)){
        std::istringstream iss(linea);
        Users usuario;
        std::getline(iss, mail, ',');
        iss >> edad;
        iss.ignore();
        std::getline(iss, pais, ',');
        insert_user(User, mail, edad, pais);
    }
    archivo.close();
}
//Parte Usuarios

void menu_user(){
    int option, age;
    string mail, country;
    cout<<"1. Agregar usuario\n";
    cout<<"2. Mostrar usuario\n";
    cout<<"3. Eliminar un usuario\n";
    cout<<"4. Calificacion\n";
    cout<<"5. Reseña\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba su mail\n";
                getline(cin,mail);
                cout<<"Escriba su edad\n";
                cin>>age;
                cin.ignore(1000,'\n');
                cout<<"Escriba su pais de origen\n";
                getline(cin,country);
                insert_user(User, mail, age, country);
                break;

        case 2: show_users(User);
                break;

        case 3: cout<<"Escriba el correo del usuario que desee eliminar\n";
                getline(cin,mail);
                delete_a_user(User,mail);
                break;
            
        case 4: cout<<"----CALIFICACIONES----\n";
                cout<<"1. Peliculas\n";
                cout<<"2. Series\n";
                cin>>option;
                if(option==1){
                    menu_qualification_movie();
                }
                else if(option==2){
                    menu_qualification_serie();
                }
                break;
    }
}

void insert_user(Users *&User, string m, int a, string c){
    Users *new_user = new Users;
    new_user -> mail = m;
    new_user -> age = a;
    new_user -> country = c;
    Users *aux1 = User;
    Users *aux2;

    while(aux1 != NULL){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }

    if(User == aux1){
        User = new_user;
    }
    else{
        aux2 -> next = new_user;
    }
    new_user -> next = aux1;
    new_user -> qualifications_movies = aux1;
    new_user -> qualifications_series = aux1;
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

void menu_qualification_movie(){
    int option;
    float score;
    string mail_user, name_movie;
    cout<<"----------Peliculas------------\n";
    cout<<"1.Agregar una calificacion\n";
    cout<<"2.Top 5 mejores calificadas\n";
    cout<<"3. Mostrar calificaciones\n";
    cout<<"4. Eliminar una calificacion\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba su mail de usuario\n";
                getline(cin,mail_user);
                if((buscar_user(User,mail_user)) == true){
                    cout<<"Escriba la pelicula a la que le quiera hacer la calificacion\n";
                    getline(cin,name_movie);
                    if((buscar_movie(Movie,name_movie)) == true){
                        cout<<"Calificacion (0.0 al 5.0)\n";
                        cin>>score;
                        if((score>(-0.1))and(score<(5.1))){
                            add_qualification_movie(User,mail_user,name_movie,score);
                        }
                        else{
                            cout<<"Calificacion fuera de rango";
                        }
                    }
                    else{
                    cout<<"No hay ninguna pelicula con ese nombre\n";
                    }
                }
                else{
                    cout<<"No hay ningun usuario con ese mail\n";
                }
                break;
        
        case 2: 
                break;

        case 3: cout<<"Escriba su mail de usuario\n";
                getline(cin,mail_user);
                show_qualification_movie(User,mail_user);
                break;

        case 4: cout<<"Escriba su mail de usuario\n";
                getline(cin,mail_user);
                if((buscar_user(User,mail_user)) == true){
                    cout<<"Escriba el nombre de la pelicula a la cual quiere eliminar su calificacion\n";
                    getline(cin,name_movie);
                    if((buscar_movie(Movie,name_movie)) == true){
                        delete_a_qualification_movie(User, mail_user, name_movie);
                    }
                    else{
                        cout<<"No hay ninguna pelicula con ese nombre";
                    }
                }
                else{
                    cout<<"No hay ningun usuario con ese mail\n";
                }
                break;
    }
}

void add_qualification_movie(Users *&User, string m, string n, float s){
    Users *new_qualification = new Users;
    new_qualification -> name = n;
    new_qualification -> score = s;
    Users *aux1 = User;
    Users *aux2;
    bool bandera=false;
    while(((aux1 -> mail)!= m )&&((aux1 != NULL))){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }
    aux2 = aux1 -> qualifications_movies;
    while(aux2 != NULL){
        if((aux2 -> name)==n){
            bandera = true;
        }
        aux2 = aux2 -> qualifications_movies;
    }
    aux2 = aux1 -> qualifications_movies;
    if(bandera == false){
        if(aux2==NULL){
        aux1 -> qualifications_movies = new_qualification;
        new_qualification -> qualifications_movies = aux2;
        }
        else{
            while(aux2 != NULL){
                aux1 = aux2;
                aux2 = aux2 -> qualifications_movies;
            }
            aux1 -> qualifications_movies = new_qualification;
            new_qualification -> qualifications_movies = aux2;
        }
        cout<<"Agregado exitosamente\n";
        cout<<"\n";
    }
    else{
        cout<<"Ya realizaste una calificacion sobre esta pelicula\n";
        cout<<"\n";
    }

}

void show_qualification_movie(Users *User, string m){
    Users *aux1 = User;
    
    while(((aux1 -> mail)!= m )&&((aux1 != NULL))){
        aux1 = aux1 -> next;
    }
    aux1 = aux1 -> qualifications_movies;
    while(aux1 != NULL){
        cout<<"\n";
        cout<<"Pelicula: "<<aux1 -> name<<"\n";
        cout<<"Calificacion: "<<aux1 -> score<<"\n";
        aux1 = aux1 -> qualifications_movies;
    }
}

void delete_a_qualification_movie(Users *&User, string m, string n){
    if (User!=NULL){
        Users *aux1 = User;
        Users *aux2,*aux3;

        while(((aux1 -> mail)!= m )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> next;
        }
        aux2 = aux1 -> qualifications_movies;
        aux3 = aux2;
        while(((aux2 -> name)!= n )&&((aux1 != NULL))){
            aux3 = aux2;
            aux2 = aux2 -> qualifications_movies;
        }
        if(aux2==aux3){
            aux2 = aux2 -> qualifications_movies;
            aux1 -> qualifications_movies = aux2;
            delete aux3;
        }
        else{
            aux3 -> qualifications_movies = aux2 -> qualifications_movies;
            delete aux2;
        }
        cout<<"Eliminado exitosamente\n";
        cout<<"\n";
    }
}

void menu_qualification_serie(){
    int option;
    float score;
    string mail_user, name_serie;
    cout<<"----------Series------------\n";
    cout<<"1.Agregar una calificacion\n";
    cout<<"2.Top 5 mejores calificadas\n";
    cout<<"3. Mostrar calificaciones\n";
    cout<<"4. Eliminar una calificacion\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba su mail de usuario\n";
                getline(cin,mail_user);
                if((buscar_user(User,mail_user)) == true){
                    cout<<"Escriba la serie a la que le quiera hacer la calificacion\n";
                    getline(cin,name_serie);
                    if((buscar_serie(Serie,name_serie)) == true){
                        cout<<"Calificacion (0.0 al 5.0)\n";
                        cin>>score;
                        if((score>(-0.1))and(score<(5.1))){
                            add_qualification_serie(User,mail_user,name_serie,score);
                        }
                        else{
                            cout<<"Calificacion fuera de rango";
                        }
                    }
                    else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                    }
                }
                else{
                    cout<<"No hay ningun usuario con ese mail\n";
                }
                break;
        
        case 2: 
                break;

        case 3: cout<<"Escriba su mail de usuario\n";
                getline(cin,mail_user);
                show_qualification_serie(User,mail_user);
                break;

        case 4: cout<<"Escriba su mail de usuario\n";
                getline(cin,mail_user);
                if((buscar_user(User,mail_user)) == true){
                    cout<<"Escriba el nombre de la pelicula a la cual quiere eliminar su calificacion\n";
                    getline(cin,name_serie);
                    if((buscar_serie(Serie,name_serie)) == true){
                        delete_a_qualification_serie(User, mail_user, name_serie);
                    }
                    else{
                        cout<<"No hay ninguna serie con ese nombre";
                    }
                }
                else{
                    cout<<"No hay ningun usuario con ese mail\n";
                }
                break;
    }
}

void add_qualification_serie(Users *&User, string m, string n, float s){
    Users *new_qualification = new Users;
    new_qualification -> name = n;
    new_qualification -> score = s;
    Users *aux1 = User;
    Users *aux2;
    bool bandera=false;
    while(((aux1 -> mail)!= m )&&((aux1 != NULL))){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }
    aux2 = aux1 -> qualifications_series;
    while(aux2 != NULL){
        if((aux2 -> name)==n){
            bandera = true;
        }
        aux2 = aux2 -> qualifications_series;
    }
    aux2 = aux1 -> qualifications_series;
    if(bandera == false){
        if(aux2==NULL){
        aux1 -> qualifications_series = new_qualification;
        new_qualification -> qualifications_series = aux2;
        }
        else{
            while(aux2 != NULL){
                aux1 = aux2;
                aux2 = aux2 -> qualifications_series;
            }
            aux1 -> qualifications_series = new_qualification;
            new_qualification -> qualifications_series = aux2;
        }
        cout<<"Agregado exitosamente\n";
        cout<<"\n";
    }
    else{
        cout<<"Ya realizaste una calificacion sobre esta pelicula\n";
        cout<<"\n";
    }

}

void show_qualification_serie(Users *User, string m){
    Users *aux1 = User;
    
    while(((aux1 -> mail)!= m )&&((aux1 != NULL))){
        aux1 = aux1 -> next;
    }
    aux1 = aux1 -> qualifications_series;
    while(aux1 != NULL){
        cout<<"\n";
        cout<<"Serie: "<<aux1 -> name<<"\n";
        cout<<"Calificacion: "<<aux1 -> score<<"\n";
        aux1 = aux1 -> qualifications_series;
    }
}

void delete_a_qualification_serie(Users *&User, string m, string n){
    if (User!=NULL){
        Users *aux1 = User;
        Users *aux2,*aux3;

        while(((aux1 -> mail)!= m )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> next;
        }
        aux2 = aux1 -> qualifications_series;
        aux3 = aux2;
        while(((aux2 -> name)!= n )&&((aux1 != NULL))){
            aux3 = aux2;
            aux2 = aux2 -> qualifications_series;
        }
        if(aux2==aux3){
            aux2 = aux2 -> qualifications_series;
            aux1 -> qualifications_series = aux2;
            delete aux3;
        }
        else{
            aux3 -> qualifications_series = aux2 -> qualifications_series;
            delete aux2;
        }
        cout<<"Eliminado exitosamente\n";
        cout<<"\n";
    }
}


//Parte series
void menu_series_general(){
    int option;
    cout<<"1. Series\n";
    cout<<"2. Temporadas\n";
    cout<<"3. Capitulos\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: menu_series();
                break;

        case 2: menu_seasons();
                break;

        case 3: menu_chapters();
                break;
    }
}

void menu_series(){
    int option, year;
    string name, genre;
    cout<<"1. Agregar serie\n";
    cout<<"2. Mostrar series\n";
    cout<<"3. Eliminar series\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba el nombre de la serie\n";
                getline(cin,name);
                cout<<"Escriba su año de lanzamiento\n";
                cin>>year;
                cin.ignore(1000,'\n');
                cout<<"Escriba su genero\n";
                getline(cin,genre);
                insert_series(Serie, name, year, genre);
                break;

        case 2: show_series(Serie);
                break;

        case 3: cout<<"Escriba la serie que quiera eliminar\n";
                getline(cin,name);
                if((buscar_serie(Serie,name)) == true){
                    delete_a_serie(Serie,name);
                }
                else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                }
                break;
    }
}

void insert_series(Series *&Serie, string n, int yr, string g){
    Series *new_serie = new Series;
    new_serie -> name_serie = n;
    new_serie -> year_released = yr;
    new_serie -> genre = g;
    Series *aux1 = Serie;
    Series *aux2;

    while(aux1 != NULL){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }

    if(Serie == aux1){
        Serie = new_serie;
    }
    else{
        aux2 -> next = new_serie;
    }
    new_serie -> next = aux1;
    new_serie -> seasons = aux1;
}

void show_series(Series *Serie){
    Series *aux1 = Serie;
    while(aux1 != NULL){
        cout<<aux1 -> name_serie<<"\n";
        cout<<aux1 -> year_released<<"\n";
        cout<<aux1 -> genre<<"\n";
        cout<<"\n";
        aux1 = aux1 -> next;
    }
}

void delete_a_serie(Series *&Serie, string n){
    if (Serie!=NULL){
        Series *aux1 = Serie;
        Series *aux2, *aux3, *aux4;

        while(((aux1 -> name_serie)!= n )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> next;
        }
        aux2 = aux1 -> seasons;
        while(aux2 != NULL){
            if((aux2 -> chapters)!=NULL){
                aux3 = aux2 -> chapters;
                while(aux3!=NULL){
                    aux4 = aux3;
                    aux3 = aux3 -> chapters;
                    delete aux4; 
                }
            }
            aux2 = aux2 -> seasons;
        }
        aux2 = aux1 -> seasons;
        while(aux2!=NULL){
            aux3 = aux2;
            aux2 = aux2 -> seasons;
            delete aux3; 
        }
        if(Serie==aux1){
            Serie = Serie -> next;
            delete aux1;
        }
        else{
            aux4 = Serie;
            while((aux4 -> next)!=aux1){
                aux4 = aux4 -> next;
            }
            aux4 -> next = aux1 -> next; 
            delete aux1;
        }
        cout<<"Eliminado exitosamente\n";
        cout<<"\n";
    }
}

void menu_seasons(){
    int option, year;
    string name, name_serie;
    cout<<"1. Agregar temporada\n";
    cout<<"2. Mostrar temporadas\n";
    cout<<"3. Eliminar temporada\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba la serie a la que pertenece la temporada\n";
                getline(cin,name_serie);
                if((buscar_serie(Serie,name_serie)) == true){
                    cout<<"Escriba el nombre de la temporada\n";
                    getline(cin,name);
                    cout<<"Escriba su año de lanzamiento\n";
                    cin>>year;
                    cin.ignore(1000,'\n');
                    insert_seasons(Serie, name, year, name_serie);
                    break;
                }
                else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                }
                break;

        case 2: cout<<"Escriba la serie de la cual quiere ver sus temporadas\n";
                getline(cin,name_serie);
                if((buscar_serie(Serie,name_serie)) == true){
                    show_seasons(Serie,name_serie);
                }
                else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                }
                break;

        case 3: cout<<"Escriba la serie de la temporada que quiera eliminar\n";
                getline(cin,name_serie);
                if((buscar_serie(Serie,name_serie)) == true){
                    cout<<"Escriba la temporada que quiera eliminar\n";
                    getline(cin,name);
                    delete_a_season(Serie,name,name_serie);
                }
                break;
    }
}

void insert_seasons(Series *&Serie, string n, int yr, string ns){
    Series *new_season = new Series;
    new_season -> name_season = n;
    new_season -> year_released = yr;
    Series *aux1 = Serie;
    Series *aux2;
    while(((aux1 -> name_serie)!= ns )&&((aux1 != NULL))){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }
    aux2 = aux1 -> seasons;
    if(aux2==NULL){
        aux1 -> seasons = new_season;
        new_season -> seasons = aux2;
    }
    else{
        while(aux2 != NULL){
            aux1 = aux2;
            aux2 = aux2 -> seasons;
        }
        aux1 -> seasons = new_season;
        new_season -> seasons = aux2;
    }
    new_season -> chapters = aux2;
}

void show_seasons(Series *Serie, string n){
    Series *aux1 = Serie;
    while(((aux1 -> name_serie)!= n )&&((aux1 != NULL))){
        aux1 = aux1 -> next;
    } 
    aux1 = aux1 -> seasons;
    while(aux1 != NULL){
        cout<<"\n";
        cout<<aux1 -> name_season<<"\n";
        cout<<aux1 -> year_released<<"\n";
        aux1 = aux1 -> seasons;
    }
}

void delete_a_season(Series *&Serie, string n, string ns){
    if (Serie!=NULL){
        Series *aux1 = Serie;
        Series *aux2, *aux3, *aux4, *aux5;

        while(((aux1 -> name_serie)!= ns )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> next;
        }
        aux5=aux1;
        aux2 = aux1 -> seasons;
        aux1=aux2;
        aux4=aux2;
        while(((aux1 -> name_season)!= n )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> seasons;
        }
        aux2 = aux1 -> chapters;

        while(aux2!=NULL){
            aux3=aux2;
            aux2=aux2->chapters;
            delete aux3;
        }
        if(aux4==aux1){
            aux1=aux1->seasons;
            delete aux4;
            aux5 -> seasons = aux1;
        }
        else{
            aux2=aux4;
            while((aux2 -> seasons)!=aux1){
                aux2 = aux2 -> seasons;
            }
            aux2 -> seasons = aux1 -> seasons;
            delete aux1;
        }
        cout<<"Eliminado exitosamente\n";
        cout<<"\n";
    }
}

void menu_chapters(){
    int option, year, lenght, chapter_number;
    string name, name_serie, name_season;
    cout<<"1. Agregar capitulo\n";
    cout<<"2. Mostrar capitulos\n";
    cout<<"3. Eliminar capitulo\n";
    cin>>option;
    cin.ignore(1000,'\n');
    switch(option){
        case 1: cout<<"Escriba la serie a la que pertenece el capitulo\n";
                getline(cin,name_serie);
                if((buscar_serie(Serie,name_serie)) == true){
                    cout<<"Escriba la temporada a la que pertenece el capitulo\n";
                    getline(cin,name_season);
                    if((buscar_season(Serie,name_serie,name_season)) == true){
                        cout<<"Escriba el nombre del capitulo\n";
                        getline(cin,name);
                        cout<<"Escriba su año de lanzamiento\n";
                        cin>>year;
                        cin.ignore(1000,'\n');
                        cout<<"Duracion en minutos\n";
                        cin>>lenght;
                        cout<<"Numero de capitulo\n";
                        cin>>chapter_number;
                        insert_chapters(Serie, name, year, lenght, chapter_number,name_serie, name_season);
                    }
                    else{
                        cout<<"No hay ninguna temporada con ese nombre\n";
                    }
                }
                else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                }
                break;

        case 2: cout<<"Escriba la serie de la cual quiere ver sus capitulos\n";
                getline(cin,name_serie);
                if((buscar_serie(Serie,name_serie)) == true){
                    cout<<"Escriba la temporada de la cual quiere ver sus capitulos\n";
                    getline(cin,name_season);
                    if((buscar_season(Serie,name_serie,name_season)) == true){
                        show_chapters(Serie,name_serie, name_season);
                    }
                    else{
                        cout<<"No hay ninguna temporada con ese nombre\n";
                    }
                }
                else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                }
                break;

        case 3: cout<<"Escriba la serie del capitulo que quiera eliminar\n";
                getline(cin,name_serie);
                if((buscar_serie(Serie,name_serie)) == true){
                    cout<<"Escriba la temporada del capitulo que quiera eliminar\n";
                    getline(cin,name_season);
                    if((buscar_season(Serie,name_serie,name_season)) == true){
                        cout<<"Escriba el nombre del capitulo que quiera eliminar\n";
                        getline(cin,name);
                        delete_a_chapter(Serie,name,name_serie,name_season);
                    }
                    else{
                        cout<<"No hay ninguna temporada con ese nombre\n";
                    }
                }
                else{
                    cout<<"No hay ninguna serie con ese nombre\n";
                }
                break;
    }
}

void insert_chapters(Series *&Serie, string n, int yr, int l, int cn, string ns, string nse){
    Series *new_chapter = new Series;
    new_chapter -> name_chapter = n;
    new_chapter -> year_released = yr;
    new_chapter -> lenght = l;
    new_chapter -> chapter_number = cn;
    Series *aux1 = Serie;
    Series *aux2;
    while(((aux1 -> name_serie)!= ns )&&((aux1 != NULL))){
        aux2 = aux1;
        aux1 = aux1 -> next;
    }
    aux2 = aux1 -> seasons;
    aux1=aux2;
    while(((aux1 -> name_season)!= nse )&&((aux1 != NULL))){
        aux2 = aux1;
        aux1 = aux1 -> seasons;
    }
    aux2 = aux1 -> chapters;
    if(aux2==NULL){
        aux1 -> chapters = new_chapter;
        new_chapter -> chapters = aux2;
    }
    else{
        while(aux2 != NULL){
            aux1 = aux2;
            aux2 = aux2 -> chapters;
        }
        aux1 -> chapters = new_chapter;
        new_chapter -> chapters = aux2;
    }
}

void show_chapters(Series *Serie, string n, string ns){
    Series *aux1 = Serie;
    while(((aux1 -> name_serie)!= n )&&((aux1 != NULL))){
        aux1 = aux1 -> next;
    } 
    aux1 = aux1 -> seasons;
    while(((aux1 -> name_season)!= ns )&&((aux1 != NULL))){
        aux1 = aux1 -> seasons;
    } 
    aux1 = aux1 -> chapters;
    while(aux1 != NULL){
        cout<<"\n";
        cout<<aux1 -> name_chapter<<"\n";
        cout<<aux1 -> year_released<<"\n";
        cout<<aux1 -> lenght<<"\n";
        cout<<aux1 -> chapter_number<<"\n";
        aux1 = aux1 -> chapters;
    }
}

void delete_a_chapter(Series *&Serie, string n, string ns, string nse){
    if (Serie!=NULL){
        Series *aux1 = Serie;
        Series *aux2, *aux3;

        while(((aux1 -> name_serie)!= ns )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> next;
        }
        aux2 = aux1 -> seasons;
        aux1=aux2;
        while(((aux1 -> name_season)!= nse )&&((aux1 != NULL))){
            aux2 = aux1;
            aux1 = aux1 -> seasons;
        }
        aux2 = aux1 -> chapters;
        aux3=aux2;
        while((aux2->name_chapter!=n)&&(aux2!=NULL)){
            aux3=aux2;
            aux2=aux2->chapters;
        }

        if(aux2==aux3){
            aux2=aux2->chapters;
            delete aux3;
            aux1 -> chapters = aux2;
        }
        else{
            aux3->chapters=aux2->chapters;
            delete aux2;
        }
        cout<<"Eliminado exitosamente\n";
        cout<<"\n";
    }
}


bool buscar_serie(Series *Serie,string n){
    bool bandera = false;
    Series *p = Serie;

    while(p!=NULL){
        if(p->name_serie==n){
            bandera = true;
        }
        p=p->next;
    }

    if(bandera){
        return true;
    }
    else{
        return false;
    }
}

bool buscar_season(Series *Serie,string n, string ns){
    bool bandera = false;
    Series *p = Serie;
    
    while(((p -> name_serie)!= n )&&((p != NULL))){
        p = p -> next;
    } 
    p = p -> seasons;
    while(p!=NULL){
        if(p->name_season==ns){
            bandera = true;
        }
        p = p -> seasons;
    }
    
    if(bandera){
        return true;
    }
    else{
        return false;
    }
}

bool buscar_user(Users *User,string n){
    bool bandera = false;
    Users *p = User;
    
    while(p!=NULL){
        if(p->mail==n){
            bandera = true;
        }
        p=p->next;
    }

    if(bandera){
        return true;
    }
    else{
        return false;
    }
}

bool buscar_movie(Movies *Movie,string n){
    bool bandera = false;
    Movies *p = Movie;
    
    while(p!=NULL){
        if(p->name_movie==n){
            bandera = true;
        }
        p=p->next;
    }

    if(bandera){
        return true;
    }
    else{
        return false;
    }
}