#include <stdio.h>
#include <string.h>
#include <iostream> 
#include <stdlib.h>
#include <locale>
using namespace std;
 
// Если при дешифровании положение элемента(дешифрованного) меньше нуля, то
int abs(int NumK,int lenAlph){
       while(NumK < 0) NumK+=lenAlph;
       return NumK%lenAlph;
}
 
 //Функция справки
 void help(){
    setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали // вызов функции настройки локали
    cout << "$ crypt [options] <key> <source> [<dest>]\n";
    cout << "options:\n";
    cout << "    -a, --alphabet=<alphabet>  alphabet — алфавит для работы алгоритма (по умолчанию \n";
    cout << "                               содержит буквы из латниского алфавита и цифры: AaBbCc..Zz0..9)\n";
    cout << "    -t, --type=<type>          type может быть 'encode' или 'decode', по умолчанию — encode \n";
    cout << "    -h, --help                 выводит эту справку\n";
    cout << "key:\n";
    cout << "  ключ для шифрования/дешифрования\n";
    cout << "source:\n";
    cout << "  исходный файл для шифрования/дешифрования\n";
    cout << "dest:\n";
    cout << "файл, куда будет записан новый, зашифрованный текст. Если не указан, то переписывает source" <<endl;
}
 
 
int main(int argc, char *argv[]){
  string Alphabet="AaBbCcDdEeFfGgHhIiKkLlMmNnOoPpQqRrSsTtVvXxYyZz0123456789";
  string type ="encode";
  int  keyNum,i, num;
  int key=0;//обнуляем переменную,чтобы если порядок введенных данных неправильный,то проверить условие,что файл встретился,а ключ все еще 0
  if (string(argv[1])=="-h" or string(argv[1])=="--help") {help(); return -1;}
  else if (argc<3 or argc>8) {
    setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
    cout <<"!Ошибка! Неправильно введены данные!"<<endl;
        return -1;
    }/* Минимальное количество передаваемых аргументов должно быть три
      (имя программы,ключ для шифрования,исходный файл)*/

 
   else if (argc>2){
        for (i=1; i<argc; i++){  //в функции argv нулевой элемент -имя программы,поэтому начинаем с первого элемента просматривать аргументы
 
            std::string arg=string(argv[i]);
			
            //алфавит
            if(arg=="-a"){ //если введен параметр -а то считываем алфавит на позиции I+1(если ,конечно,это алфавит ;))
                if(string(argv[i+1])=="-t" and (string(argv[i+2])=="encode" or string(argv[i+2])=="decode")) {
                    // если следующий аргумент это параметр,то неверно введен алфавит
                    setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
                    cout <<"!!Ошибка! Неверно заданы параметры!"<<endl;
                    return -1;
                    }
				else  {i++;Alphabet= string(argv[i]); cout<<Alphabet<<" ALPHABET\n";}
                   
				}
            else if(arg.substr(0,10)=="--alphabet="){ //если введен параметр --alphabet=,то с этого же аргумента списываем введенный алфавит
                Alphabet=arg.substr(11);
                }
            //тип кодирования
			else if(arg.substr(0,6)== "--type="){ type = arg.substr(7);
			        if (!((type == "encode") or (type =="decode"))){ //если type!=одному из вариантов кодирования,то ошибка! Неверно заданы параметры!
                        setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
                        cout <<"Ошибка! Неверно заданы параметры!"<<endl;
                        return -1;
                    }
				} 
            else if(arg == "-t"){ //записываем тип кодирования.
                    i++;
					type=string(argv[i]);
                    if (!((type == "encode") or (type =="decode"))){ //если type!=одному из вариантов кодирования,то ошибка! Неверно заданы параметры!
                        setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
                        cout <<"Ошибка! Неверно заданы параметры!"<<endl;
                        return -1;
                    }
                }
            else if(key=atoi(argv[i])){ //если функция возвращает ненулевое значние,то это ключ
				    if (atoi(argv[i]) < 1){ //если ключ отрицательный или ноль,то ошибка
					   setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
                       cout <<"Ошибка! Ключ отрицательный!"<<endl;
                       return -1;				  
				       }
				    keyNum = i;//Запомним номер ключа в строке аргументов,чтобы узнать куда нам записать зашифрованную комбинацию.
					key=atoi(argv[i]);//запомним ключ
				    break;
			        }
			else{
              cout << "Ошибка!2" << endl;//если введено что-то не то
                  return -1;	
                }
    }
  
    // Если требуется декодировать, поменяем знак ключа на -
    if (type=="decode") key= -key;
 
    // начинаем работать непосредственно с самими файлами
    FILE * source;
    FILE * dest;
 
    if (keyNum == (argc-2)){ // вспомним,что просматривать файлы начали не с 0 аргумента,а с 1. если ключ предпоследний аргумент
        if (!(source = fopen(argv[argc-1],"rt"))){ // проверим существует ли этот файл
            setlocale(LC_CTYPE, "rus");
            cout <<"!!!!Ошибка! Файл не существует!"<<endl;
            return -1;
            }
        source=fopen(argv[argc-1],"rt+");
        dest=source; //так как введен один файл,то вывод будет осуществляться в него
        }
 
    else if (keyNum == (argc-3)){ // если введено два файла
        if (!(source = fopen(argv[argc-2],"rt"))){ // проверим существует ли этот файл
                setlocale(LC_CTYPE, "rus");
                cout <<"!!!!!Ошибка! Файл не существует!"<<endl;
                return -1;
                }
        else source=fopen(argv[argc-2],"rt");//открываем для чтения
        if (!(dest=fopen(argv[argc-1],"wt"))){ // проверим существует ли этот файл
            setlocale(LC_CTYPE, "rus");
            cout <<"!!!!!!Ошибка! Файл не существует!"<<endl;
            return -1;
            }
        else  dest=fopen(argv[argc-1],"wt");//открываем для записи
        }
 
 
   char ch;
 
     while ((ch=fgetc(source)) != EOF){ //читать пока не конец файла

        // Если dest отсутсвует, то  перезаписываем каждый символ
        if(dest == source) fseek( dest , -1 , SEEK_CUR );// если файл введен один,то перезаписываем каждый символ в нем.
        if(Alphabet.find(ch)) { //если символ в алфавите есть то шифруем или дешифруем
            num=Alphabet.find(ch);
            ch=Alphabet[abs((num + key),Alphabet.length())];
            }
        // Записываем результат
        fputc(ch,dest);
        }
    
    fclose(source);
    fclose(dest);
    return 0;
}
}