#include <iostream>
#include <cassert>

#include "set.h"
#include "voce.h"

// Funtore operatore di uguaglianza per interi
struct equal_int {
    bool operator()(const int a, const int b) const {
    	return a==b;
    }
};

// Dispari
struct is_odd {		
    bool operator()(const int a) const {
    	return (a%2)!=0;
    }
};

// Pari
struct is_even {	
    bool operator()(const int a) const {
    	return (a%2)==0;
    }
};

// Funtore operatore di uguaglianza per stringhe
struct equal_string {
	bool operator()(const std::string a, const std::string b) const {
		return (!a.compare(b));
	}
};

// Lunghezza uguale a 3
struct check_size_3 {
	bool operator()(const std::string a) const {
		return a.size()==3;
	}
};

// Lunghezza diversa da 3
struct check_size_not_3 {
	bool operator()(const std::string a) const {
		return a.size()!=3;
	}
};

// Funtore operatore di uguaglianza per voci
struct equal_voce {
    bool operator()(const voce a, const voce b) const {
    	return a==b;
    }
};

// Funzione che ritorna true sse il nome della voce passata 
// finisce con la lettera 'o'
struct check_nome_o {
	bool operator()(const voce &v) const {
	std::string nome = v.nome;

	char lastc = nome[nome.size()-1];
	return lastc == 'o'; 
	}
};

// Funzione che ritorna true sse il nome della voce passata 
// NON finisce con la lettera 'o'
struct check_nome_not_o {
	bool operator()(const voce &v) const {
	std::string nome = v.nome;

	char lastc = nome[nome.size()-1];
	return lastc != 'o'; 
	}
};

void test_int() {
	typedef set<int, equal_int> set_type;
	
	std::cout << "TEST NUMERI INTERI" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;

	// Costruttore default
	set_type set1;   
	std::cout << "Set1 => Costruttore di default" << std::endl;
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Aggiunta elementi
	std::cout << "Set1 => Add(1, 10, 20, 55, 56, 57, 58, 59, 60)" << std::endl;
	try {
		set1.add(1);
		set1.add(10);
		set1.add(20);
		set1.add(55);
		set1.add(56);
		set1.add(57);
		set1.add(58);
		set1.add(59);
		set1.add(60);
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set1.count() == 9);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Generazione add_exception
	std::cout << "Set1 => Add(55)" << std::endl;
	try {     
		set1.add(55);
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	}
	assert(set1.count() == 9);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Aggiunta elementi dopo add_exception
	std::cout << "Set1 => Add(15)" << std::endl;
	try {     
		set1.add(15);
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	}
	assert(set1.count() == 10);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Rimozione elementi
	std::cout << "Set1 => Remove(55, 56, 57, 58, 59, 60)" << std::endl;
  	try {
		set1.remove(55);
		set1.remove(56);
		set1.remove(57);
		set1.remove(58);
		set1.remove(59);
		set1.remove(60);	// Rimozione elemento in coda

	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set1.count() == 4);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Generazione remove_exception
	std::cout << "Set1 => Remove(55)" << std::endl;
	try {     
		set1.remove(55);
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	}
	assert(set1.count() == 4);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Rimozione elemento in testa dopo remove_exception
	std::cout << "Set1 => Remove(1)" << std::endl;
	try {     
		set1.remove(1);
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	}
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Copy Constructor 
	set_type set2(set1);   
	std::cout << "Set2 => Copy Constructor(Set1)" << std::endl;
	assert(set2.count() == 3);
	std::cout << "Set2:" << set2 << std::endl;
	std::cout << "Count Set2: " << set2.count() << std::endl << std::endl;

	// Iterator Constructor 
	set<int, equal_int>::const_iterator begin = set1.begin();
	set<int, equal_int>::const_iterator end = set1.end();
	
	set_type set3(begin, end);
	std::cout << std::endl << "Set3 => Iterator Constructor(Set1)" << std::endl;
	assert(set3.count() == 3);
	std::cout << "Set3: " << set3 << std::endl;
	std::cout << "Count Set3: " << set3.count() << std::endl << std::endl;

	// Rimozione di tutti gli elementi di s3
	std::cout << "Set3 => Remove(10, 15, 20)" << std::endl;
  	try {
		set3.remove(10);
		set3.remove(15);
		set3.remove(20);
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set3.count() == 0);
	std::cout << "Set3:" << set3 << std::endl;
	std::cout << "Count Set3: " << set3.count() << std::endl << std::endl;

	// Operatore di assegnamento con set vuoto a destra dell'operatore
	std::cout << std::endl << "Set2=Set3 => Operatore di assegnamento" << std::endl;
	set2 = set3;
	assert(set2.count() == 0);
	std::cout << "Set2:" << set2 << std::endl;
	std::cout << "Count Set2: " << set2.count() << std::endl << std::endl;

	// Copy Constructor su set vuoto
	set_type set4(set2);   
	std::cout << "Set4 => Copy Constructor(Set2)" << std::endl;
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore di assegnamento con set vuoto a sinistra dell'operatore
	std::cout << std::endl << "Set4=Set1 => Operatore di assegnamento" << std::endl;
	set4 = set1;
	assert(set4.count() == 3);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Iterator Constructor su set vuoto
	begin = set3.begin();
	end = set3.end();
	set_type set5(begin, end);
	std::cout << std::endl << "Set5 => Iterator Constructor(Set3)" << std::endl;
	assert(set5.count() == 0);
	std::cout << "Set5: " << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Aggiunta elementi con add_exception
	std::cout << "Set5 => Add(30, 31, 32, 33, 32)" << std::endl;
	try {
		set5.add(30);
		set5.add(31);
		set5.add(32);
		set5.add(33);
		set5.add(32);
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Operatore di assegnamento con entrambi i set NON vuoti
	std::cout << std::endl << "Set4=Set5 => Operatore di assegnamento" << std::endl;
	set4 = set5;
	assert(set4.count() == 4);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Rimozione elementi con remove_exception
	std::cout << "Set4 => Remove(30, 31, 32, 33, 32)" << std::endl;
  	try {
		set4.remove(30);
		set4.remove(31);
		set4.remove(32);
		set4.remove(33);
		set4.remove(32);
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore di assegnamento con entrambi i set vuoti
	std::cout << std::endl << "Set4=Set3 => Operatore di assegnamento" << std::endl;
	set4 = set3;
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore[] in lettura
	std::cout << "Set1 => Operatore[]" << std::endl;
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;
  	try {
  		std::cout << "Set1[0]:" << set1[0] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Operatore[] con index_exception
	std::cout << "Set5 => Operatore[]" << std::endl;
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;
  	try {
  		std::cout << "Set5[0]:" << set5[0] << std::endl;
  		std::cout << "Set5[1]:" << set5[1] << std::endl;
  		std::cout << "Set5[2]:" << set5[2] << std::endl;
  		std::cout << "Set5[3]:" << set5[3] << std::endl;
  		std::cout << "Set5[4]:" << set5[4] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Operatore[] in scrittura
	/*std::cout << "Set1 => Operatore[] in Scrittura" << std::endl;
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl;
  	try {
  		std::cout << "Set1[0]=3" << std::endl;
  		set1[0]=3;
  		std::cout << "Set1[0]:" << set1[0] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;*/

	std::cout << "------------------" << std::endl;
	std::cout << "FINE TEST NUMERI INTERI" << std::endl;
	std::cout << "TUTTI I TESTI SONO STATI SUPERATI" << std::endl << std::endl << std::endl;
}

void test_filter_out_int(){
	set<int, equal_int> set, even, odd, total, total_exc, total_1, total_2;

	std::cout << "TEST FILTER_OUT NUMERI INTERI" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;
	
	// Aggiunta elementi
	std::cout << "Set => Add(1, 2, 3, 4, 5, 6, 7, 8, 9)" << std::endl;
	try {
		set.add(1);
		set.add(2);
		set.add(3);
		set.add(4);
		set.add(5);
		set.add(6);
		set.add(7);
		set.add(8);
		set.add(9);
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set.count() == 9);
	std::cout << "Set:" << set << std::endl;
	std::cout << "Count Set: " << set.count() << std::endl << std::endl;

	// Il set even contiene tutti gli elementi di set che non soddisfano il predicato is_odd (quindi tutti gli elementi pari)
	std::cout << "Even => Filter_out ELEMENTI DISPARI da Set" << std::endl;	
	try {
  		even = filter_out<int, equal_int, is_odd>(set, is_odd());
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(even.count() == 4);
	std::cout << "Even:" << even << std::endl;
	std::cout << "Count Even: " << even.count() << std::endl << std::endl;
  
	// Il set odd contiene tutti gli elementi di set che non soddisfano il predicato is_even (quindi tutti gli elementi dispari)
  	std::cout << "Odd => Filter_out ELEMENTI PARI da Set" << std::endl;	  	
	try {
  	odd = filter_out<int, equal_int, is_even>(set, is_even());
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(odd.count() == 5);
	std::cout << "Odd:" << odd << std::endl;
	std::cout << "Count Odd: " << odd.count() << std::endl << std::endl;

	// Il set total contiene gli elementi dispari (even) e gli elementi pari (odd) di set 
	std::cout << "Operatore+ => Total=Even+Odd" << std::endl;
	try {
  	total = even+odd;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total.count() == 9);
	std::cout << "Total:" << total << std::endl;
	std::cout << "Count Total: " << total.count() << std::endl << std::endl;

	// Generazione add_exception concatenando set con elementi in comune
	std::cout << "Operatore+ => Total_EXC=Set+Total" << std::endl;
	try {
  	total_exc = set+total;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_exc.count() == 0);
	std::cout << "Total_EXC:" << total_exc << std::endl;
	std::cout << "Count Total_EXC: " << total_exc.count() << std::endl << std::endl;

	// Concatenazione con set vuoto a sinistra dell'operatore
	std::cout << "Operatore+ => Total_1=Total_EXC+Total" << std::endl;
	try {
  	total_1 = total_exc+total;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_1.count() == 9);
	std::cout << "Total_1:" << total_1 << std::endl;
	std::cout << "Count Total_1: " << total_1.count() << std::endl << std::endl;

	// Concatenazione con set vuoto a destra dell'operatore
	std::cout << "Operatore+ => Total_2=Total+Total_EXC" << std::endl;
	try {
  	total_2 = total+total_exc;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_2.count() == 9);
	std::cout << "Total_2:" << total_2 << std::endl;
	std::cout << "Count Total_2: " << total_2.count() << std::endl << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "FINE TEST FILTER_OUT NUMERI INTERI" << std::endl;
	std::cout << "TUTTI I TESTI SONO STATI SUPERATI" << std::endl << std::endl << std::endl;
}

void test_string() {
	typedef set<std::string, equal_string> set_type;

	std::cout << "TEST STRINGHE" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;

	// Costruttore default
	set_type set1;   
	std::cout << "Set1 => Costruttore di default" << std::endl;
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Aggiunta elementi
	std::cout << "Set1 => Add(\"topolino\", \"minni\", \"paperino\", \"paperina\", \"pippo\" \"pluto\", \"qui\", \"quo\", \"qua\")" << std::endl;
	try {
		set1.add("topolino");
		set1.add("minni");
		set1.add("paperino");
		set1.add("paperina");
		set1.add("pippo");
		set1.add("pluto");
		set1.add("qui");
		set1.add("quo");
		set1.add("qua");
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set1.count() == 9);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Generazione add_exception
	std::cout << "Set1 => Add(\"qui\")" << std::endl;
	try {     
		set1.add("qui");
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	}
	assert(set1.count() == 9);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Aggiunta elementi dopo add_exception
	std::cout << "Set1 => Add(\"clarabella\")" << std::endl;
	try {     
		set1.add("clarabella");
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	}
	assert(set1.count() == 10);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Rimozione elementi
	std::cout << "Set1 => Remove(\"paperino\", \"pippo\", \"pluto\", \"qui\", \"quo\", \"qua\")" << std::endl;
  	try {
		set1.remove("paperino");
		set1.remove("pippo");
		set1.remove("pluto");
		set1.remove("qui");
		set1.remove("quo");
		set1.remove("qua");	// Rimozione elemento in coda

	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set1.count() == 4);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Generazione remove_exception
	std::cout << "Set1 => Remove(\"qua\")" << std::endl;
	try {     
		set1.remove("qua");
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	}
	assert(set1.count() == 4);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Rimozione elemento in testa dopo remove_exception
	std::cout << "Set1 => Remove(\"topolino\")" << std::endl;
	try {     
		set1.remove("topolino");
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	}
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Copy Constructor 
	set_type set2(set1);   
	std::cout << "Set2 => Copy Constructor(Set1)" << std::endl;
	assert(set2.count() == 3);
	std::cout << "Set2:" << set2 << std::endl;
	std::cout << "Count Set2: " << set2.count() << std::endl << std::endl;

	// Iterator Constructor 
	set<std::string, equal_string>::const_iterator begin = set1.begin();
	set<std::string, equal_string>::const_iterator end = set1.end();
	
	set_type set3(begin, end);
	std::cout << std::endl << "Set3 => Iterator Constructor(Set1)" << std::endl;
	assert(set3.count() == 3);
	std::cout << "Set3: " << set3 << std::endl;
	std::cout << "Count Set3: " << set3.count() << std::endl << std::endl;

	// Rimozione di tutti gli elementi di s3
	std::cout << "Set3 => Remove(\"minni\", \"paperina\", \"clarabella\")" << std::endl;
  	try {
		set3.remove("minni");
		set3.remove("paperina");
		set3.remove("clarabella");
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set3.count() == 0);
	std::cout << "Set3:" << set3 << std::endl;
	std::cout << "Count Set3: " << set3.count() << std::endl << std::endl;

	// Operatore di assegnamento con set vuoto a destra dell'operatore
	std::cout << std::endl << "Set2=Set3 => Operatore di assegnamento" << std::endl;
	set2 = set3;
	assert(set2.count() == 0);
	std::cout << "Set2:" << set2 << std::endl;
	std::cout << "Count Set2: " << set2.count() << std::endl << std::endl;

	// Copy Constructor su set vuoto
	set_type set4(set2);   
	std::cout << "Set4 => Copy Constructor(Set2)" << std::endl;
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore di assegnamento con set vuoto a sinistra dell'operatore
	std::cout << std::endl << "Set4=Set1 => Operatore di assegnamento" << std::endl;
	set4 = set1;
	assert(set4.count() == 3);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Iterator Constructor su set vuoto
	begin = set3.begin();
	end = set3.end();
	set_type set5(begin, end);
	std::cout << std::endl << "Set5 => Iterator Constructor(Set3)" << std::endl;
	assert(set5.count() == 0);
	std::cout << "Set5: " << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Aggiunta elementi con add_exception
	std::cout << "Set5 => Add(\"tip\", \"qui\", \"quo\", \"qua\", \"tip\",)" << std::endl;
	try {
		set5.add("tip");
		set5.add("qui");
		set5.add("quo");
		set5.add("qua");
		set5.add("tip");
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Operatore di assegnamento con entrambi i set NON vuoti
	std::cout << std::endl << "Set4=Set5 => Operatore di assegnamento" << std::endl;
	set4 = set5;
	assert(set4.count() == 4);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Rimozione elementi con remove_exception
	std::cout << "Set4 => Remove(\"tip\", \"qui\", \"quo\", \"qua\", \"tip\")" << std::endl;
  	try {
		set4.remove("tip");
		set4.remove("qui");
		set4.remove("quo");
		set4.remove("qua");
		set4.remove("tip");
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore di assegnamento con entrambi i set vuoti
	std::cout << std::endl << "Set4=Set3 => Operatore di assegnamento" << std::endl;
	set4 = set3;
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore[] in lettura
	std::cout << "Set1 => Operatore[]" << std::endl;
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;
  	try {
  		std::cout << "Set1[0]:" << set1[0] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Operatore[] con index_exception
	std::cout << "Set5 => Operatore[]" << std::endl;
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;
  	try {
  		std::cout << "Set5[0]:" << set5[0] << std::endl;
  		std::cout << "Set5[1]:" << set5[1] << std::endl;
  		std::cout << "Set5[2]:" << set5[2] << std::endl;
  		std::cout << "Set5[3]:" << set5[3] << std::endl;
  		std::cout << "Set5[4]:" << set5[4] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "FINE TEST STRINGHE" << std::endl;
	std::cout << "TUTTI I TESTI SONO STATI SUPERATI" << std::endl << std::endl << std::endl;
}

void test_filter_out_string(){
	set<std::string, equal_string> set, equal_3, notequal_3, total, total_exc, total_1, total_2;

	std::cout << "TEST FILTER_OUT STRINGHE" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;
	
	// Aggiunta elementi
	std::cout << "Set => Add(\"qui\", \"topolino\", \"quo\", \"minni\", \"qua\", \"pluto\", \"tip\", \"pippo\", \"tap\")" << std::endl;
	try {
		set.add("qui");
		set.add("topolino");
		set.add("quo");
		set.add("minni");
		set.add("qua");
		set.add("pluto");
		set.add("tip");
		set.add("pippo");
		set.add("tap");
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set.count() == 9);
	std::cout << "Set:" << set << std::endl;
	std::cout << "Count Set: " << set.count() << std::endl << std::endl;

	// Il set equal_3 contiene tutti gli elementi di set con lunghezza uguale a 3 (avendo filtrato da esso tutti gli elementi che non hanno lunghezza pari a 3)
	std::cout << "Equal_3 => Filter_out ELEMENTI LUNGHEZZA != 3 da Set" << std::endl;	
  	equal_3 = filter_out<std::string, equal_string, check_size_not_3>(set, check_size_not_3());
  	assert(equal_3.count() == 5);
	std::cout << "Equal_3:" << equal_3 << std::endl;
	std::cout << "Count Equal_3: " << equal_3.count() << std::endl << std::endl;
  
	// Il set notequal_3 contiene tutti gli elementi di set con lunghezza diversa da 3 (avendo filtrato da esso tutti gli elementi che hanno lunghezza pari a 3)
  	std::cout << "NotEqual_3 => Filter_out ELEMENTI LUNGHEZZA = 3 da Set" << std::endl;	  	
  	notequal_3 = filter_out<std::string, equal_string, check_size_3>(set, check_size_3());
  	assert(notequal_3.count() == 4);
	std::cout << "NotEqual_3:" << notequal_3 << std::endl;
	std::cout << "Count NotEqual_3: " << notequal_3.count() << std::endl << std::endl;

	// Il set total contiene gli elementi con una lunghezza pari a 3 (equal_3) e con una lunghezza diversa da 3 (notequal_3) di set 
	std::cout << "Operatore+ => Total=Equal_3+NotEqual_3" << std::endl;
  	total = equal_3+notequal_3;
  	assert(total.count() == 9);
	std::cout << "Total:" << total << std::endl;
	std::cout << "Count Total: " << total.count() << std::endl << std::endl;

	// Generazione add_exception concatenando set con elementi in comune
	std::cout << "Operatore+ => Total_EXC=Set+Total" << std::endl;
	try {
  	total_exc = set+total;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_exc.count() == 0);
	std::cout << "Total_EXC:" << total_exc << std::endl;
	std::cout << "Count Total_EXC: " << total_exc.count() << std::endl << std::endl;

	// Concatenazione con set vuoto a sinistra dell'operatore
	std::cout << "Operatore+ => Total_1=Total_EXC+Total" << std::endl;
	try {
  	total_1 = total_exc+total;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_1.count() == 9);
	std::cout << "Total_1:" << total_1 << std::endl;
	std::cout << "Count Total_1: " << total_1.count() << std::endl << std::endl;

	// Concatenazione con set vuoto a destra dell'operatore
	std::cout << "Operatore+ => Total_2=Total+Total_EXC" << std::endl;
	try {
  	total_2 = total+total_exc;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_2.count() == 9);
	std::cout << "Total_2:" << total_2 << std::endl;
	std::cout << "Count Total_2: " << total_2.count() << std::endl << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "FINE TEST FILTER_OUT STRINGHE" << std::endl;
	std::cout << "TUTTI I TESTI SONO STATI SUPERATI" << std::endl << std::endl << std::endl;
}

void test_voce() {
	typedef set<voce, equal_voce> set_type;

	std::cout << "TEST VOCI" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;

	// Costruttore default
	set_type set1;   
	std::cout << "Set1 => Costruttore di default" << std::endl;
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Aggiunta elementi
	std::cout << "Set1 => Add([\"topolino\", \"ino\", \"1\"], [\"minni\", \"inni\", \"2\"], [\"paperino\", \"ino\", \"3\"], [\"paperina\", \"ina\", \"4\"], [\"pippo\", \"ippo\", \"5\"], [\"pluto\", \"uto\", \"6\"], [\"qui\", \"ui\", \"7\"], [\"quo\", \"uo\", \"8\"], [\"qua\", \"ua\", \"9\"])" << std::endl;
	try {
		set1.add(voce("topolino", "ino", "1"));
		set1.add(voce("minni", "inni", "2"));
		set1.add(voce("paperino", "ino", "3"));
		set1.add(voce("paperina", "ina", "4"));
		set1.add(voce("pippo", "ippo", "5"));
		set1.add(voce("pluto", "uto", "6"));
		set1.add(voce("qui", "ui", "7"));
		set1.add(voce("quo", "uo", "8"));
		set1.add(voce("qua", "ua", "9"));
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set1.count() == 9);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Generazione add_exception
	std::cout << "Set1 => Add([\"qui\", \"ui\", \"7\"])" << std::endl;
	try {     
		set1.add(voce("qui","ui","7"));
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	}
	assert(set1.count() == 9);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Aggiunta elementi dopo add_exception
	std::cout << "Set1 => Add([\"clarabella\", \"bella\", \"10\"])" << std::endl;
	try {     
		set1.add(voce("clarabella","bella","10"));
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	}
	assert(set1.count() == 10);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Rimozione elementi
	std::cout << "Set1 => Remove([\"paperina\", \"ina\", \"4\"], [\"pippo\", \"ippo\", \"5\"], [\"pluto\", \"uto\", \"6\"], [\"qui\", \"ui\", \"7\"], [\"quo\", \"uo\", \"8\"], [\"qua\", \"ua\", \"9\"])" << std::endl;
  	try {
		set1.remove(voce("paperina", "ina", "4"));
		set1.remove(voce("pippo", "ippo", "5"));
		set1.remove(voce("pluto", "uto", "6"));
		set1.remove(voce("qui", "ui", "7"));
		set1.remove(voce("quo", "uo", "8"));
		set1.remove(voce("qua", "ua", "9"));	// Rimozione elemento in coda

	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set1.count() == 4);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Generazione remove_exception
	std::cout << "Set1 => Remove([\"qua\", \"ua\", \"9\"])" << std::endl;
	try {     
		set1.remove(voce("qua", "ua", "9"));
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	}
	assert(set1.count() == 4);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Rimozione elemento in testa dopo remove_exception
	std::cout << "Set1 => Remove([\"topolino\", \"ino\", \"1\"])" << std::endl;
	try {     
		set1.remove(voce("topolino", "ino", "1"));
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	}
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Copy Constructor 
	set_type set2(set1);   
	std::cout << "Set2 => Copy Constructor(Set1)" << std::endl;
	assert(set2.count() == 3);
	std::cout << "Set2:" << set2 << std::endl;
	std::cout << "Count Set2: " << set2.count() << std::endl << std::endl;

	// Iterator Constructor 
	set<voce, equal_voce>::const_iterator begin = set1.begin();
	set<voce, equal_voce>::const_iterator end = set1.end();
	
	set_type set3(begin, end);
	std::cout << std::endl << "Set3 => Iterator Constructor(Set1)" << std::endl;
	assert(set3.count() == 3);
	std::cout << "Set3: " << set3 << std::endl;
	std::cout << "Count Set3: " << set3.count() << std::endl << std::endl;

	// Rimozione di tutti gli elementi di s3
	std::cout << "Set3 => Remove([\"minni\", \"inni\", \"2\"], [\"paperino\", \"ino\", \"3\"], [\"clarabella\", \"bella\", \"10\"])" << std::endl;
  	try {
		set3.remove(voce("minni", "inni", "2"));
		set3.remove(voce("paperino", "ino", "3"));
		set3.remove(voce("clarabella","bella","10"));
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set3.count() == 0);
	std::cout << "Set3:" << set3 << std::endl;
	std::cout << "Count Set3: " << set3.count() << std::endl << std::endl;

	// Operatore di assegnamento con set vuoto a destra dell'operatore
	std::cout << std::endl << "Set2=Set3 => Operatore di assegnamento" << std::endl;
	set2 = set3;
	assert(set2.count() == 0);
	std::cout << "Set2:" << set2 << std::endl;
	std::cout << "Count Set2: " << set2.count() << std::endl << std::endl;

	// Copy Constructor su set vuoto
	set_type set4(set2);   
	std::cout << "Set4 => Copy Constructor(Set2)" << std::endl;
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore di assegnamento con set vuoto a sinistra dell'operatore
	std::cout << std::endl << "Set4=Set1 => Operatore di assegnamento" << std::endl;
	set4 = set1;
	assert(set4.count() == 3);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Iterator Constructor su set vuoto
	begin = set3.begin();
	end = set3.end();
	set_type set5(begin, end);
	std::cout << std::endl << "Set5 => Iterator Constructor(Set3)" << std::endl;
	assert(set5.count() == 0);
	std::cout << "Set5: " << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Aggiunta elementi con add_exception
	std::cout << "Set5 => Add([\"tip\", \"ip\", \"10\"], [\"qui\", \"ui\", \"7\"], [\"quo\", \"uo\", \"8\"], [\"qua\", \"ua\", \"9\"], [\"tip\", \"ip\", \"10\"])" << std::endl;
	try {
		set5.add(voce("tip", "ip", "10"));
		set5.add(voce("qui", "ui", "7"));
		set5.add(voce("quo", "uo", "8"));
		set5.add(voce("qua", "ua", "9"));
		set5.add(voce("tip", "ip", "10"));
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	// Operatore di assegnamento con entrambi i set NON vuoti
	std::cout << std::endl << "Set4=Set5 => Operatore di assegnamento" << std::endl;
	set4 = set5;
	assert(set4.count() == 4);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Rimozione elementi con remove_exception
	std::cout << "Set4 => Remove([\"tip\", \"ip\", \"10\"], [\"qui\", \"ui\", \"7\"], [\"quo\", \"uo\", \"8\"], [\"qua\", \"ua\", \"9\"], [\"tip\", \"ip\", \"10\"])" << std::endl;
  	try {
		set4.remove(voce("tip", "ip", "10"));
		set4.remove(voce("qui", "ui", "7"));
		set4.remove(voce("quo", "uo", "8"));
		set4.remove(voce("qua", "ua", "9"));	
		set4.remove(voce("tip", "ip", "10"));
	} 
	catch(remove_exception &e2) {
		std::cout << e2.what() << std::endl;
	} 
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore di assegnamento con entrambi i set vuoti
	std::cout << std::endl << "Set4=Set3 => Operatore di assegnamento" << std::endl;
	set4 = set3;
	assert(set4.count() == 0);
	std::cout << "Set4:" << set4 << std::endl;
	std::cout << "Count Set4: " << set4.count() << std::endl << std::endl;

	// Operatore[] in lettura
	std::cout << "Set1 => Operatore[]" << std::endl;
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;
  	try {
  		std::cout << "Set1[0]:" << set1[0] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set1.count() == 3);
	std::cout << "Set1:" << set1 << std::endl;
	std::cout << "Count Set1: " << set1.count() << std::endl << std::endl;

	// Operatore[] con index_exception
	std::cout << "Set5 => Operatore[]" << std::endl;
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;
  	try {
  		std::cout << "Set5[0]:" << set5[0] << std::endl;
  		std::cout << "Set5[1]:" << set5[1] << std::endl;
  		std::cout << "Set5[2]:" << set5[2] << std::endl;
  		std::cout << "Set5[3]:" << set5[3] << std::endl;
  		std::cout << "Set5[4]:" << set5[4] << std::endl;
	} 
	catch(index_exception &e3) {
		std::cout << e3.what() << std::endl;
	} 
	assert(set5.count() == 4);
	std::cout << "Set5:" << set5 << std::endl;
	std::cout << "Count Set5: " << set5.count() << std::endl << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "FINE TEST VOCI" << std::endl;
	std::cout << "TUTTI I TESTI SONO STATI SUPERATI" << std::endl << std::endl << std::endl;
}

void test_filter_out_voce(){
	set<voce, equal_voce> set, equal_o, notequal_o, total, total_exc, total_1, total_2;

	std::cout << "TEST FILTER_OUT VOCI" << std::endl;
	std::cout << "------------------" << std::endl << std::endl;

	// Aggiunta elementi
	std::cout << "Set => Add([\"qui\", \"ui\", \"7\"], [\"topolino\", \"ino\", \"1\"], [\"quo\", \"uo\", \"8\"], [\"minni\", \"inni\", \"2\"], [\"qua\", \"ua\", \"9\"], [\"pippo\", \"ippo\", \"5\"], [\"tip\", \"ip\", \"10\"], [\"pluto\", \"uto\", \"6\"], [\"tap\", \"ap\", \"11\"])" << std::endl;
	try {
		set.add(voce("qui", "ui", "7"));
		set.add(voce("topolino", "ino", "1"));
		set.add(voce("quo", "uo", "8"));
		set.add(voce("minni", "inni", "2"));
		set.add(voce("qua", "ua", "9"));
		set.add(voce("pippo", "ippo", "5"));
		set.add(voce("tip", "ip", "10"));
		set.add(voce("pluto", "uto", "6"));
		set.add(voce("tap", "ap", "11"));
	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
	assert(set.count() == 9);
	std::cout << "Set:" << set << std::endl;
	std::cout << "Count Set: " << set.count() << std::endl << std::endl;

	// Il set equal_o contiene tutti gli elementi di set con il carattere finale del nome uguale a "o" (avendo filtrato da esso tutti gli elementi con il carattere finale del nome diverso da "o")
	std::cout << "Equal_o => Filter_out ELEMENTI CON CARATTERE FINALE DEL NOME != \"O\" da Set" << std::endl;	
  	equal_o = filter_out<voce, equal_voce, check_nome_not_o>(set, check_nome_not_o());
  	assert(equal_o.count() == 4);
	std::cout << "Equal_o:" << equal_o << std::endl;
	std::cout << "Count Equal_o: " << equal_o.count() << std::endl << std::endl;
  
	// Il set notequal_o contiene tutti gli elementi di set con il carattere finale del nome diverso da "o" (avendo filtrato da esso tutti gli elementi con il carattere finale del nome uguale a "o")
  	std::cout << "NotEqual_o => Filter_out ELEMENTI CON CARATTERE FINALE DEL NOME == \"O\" da Set" << std::endl;	  	
  	notequal_o = filter_out<voce, equal_voce, check_nome_o>(set, check_nome_o());
  	assert(notequal_o.count() == 5);
	std::cout << "NotEqual_o:" << notequal_o << std::endl;
	std::cout << "Count NotEqual_o: " << notequal_o.count() << std::endl << std::endl;

	// Il set total contiene gli elementi con il carattere finale del nome uguale a "o" (equal_o) e gli elementi con il carattere finale del nome diverso da "o" (notequal_o) di set 
	std::cout << "Operatore+ => Total=Equal_o+NotEqual_o" << std::endl;
  	total = equal_o+notequal_o;
  	assert(total.count() == 9);
	std::cout << "Total:" << total << std::endl;
	std::cout << "Count Total: " << total.count() << std::endl << std::endl;

	// Generazione add_exception concatenando set con elementi in comune
	std::cout << "Operatore+ => Total_EXC=Set+Total" << std::endl;
	try {
  	total_exc = set+total;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_exc.count() == 0);
	std::cout << "Total_EXC:" << total_exc << std::endl;
	std::cout << "Count Total_EXC: " << total_exc.count() << std::endl << std::endl;

	// Concatenazione con set vuoto a sinistra dell'operatore
	std::cout << "Operatore+ => Total_1=Total_EXC+Total" << std::endl;
	try {
  	total_1 = total_exc+total;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_1.count() == 9);
	std::cout << "Total_1:" << total_1 << std::endl;
	std::cout << "Count Total_1: " << total_1.count() << std::endl << std::endl;

	// Concatenazione con set vuoto a destra dell'operatore
	std::cout << "Operatore+ => Total_2=Total+Total_EXC" << std::endl;
	try {
  	total_2 = total+total_exc;
  	} 
	catch(add_exception &e1) {
		std::cout << e1.what() << std::endl;
	} 
  	assert(total_2.count() == 9);
	std::cout << "Total_2:" << total_2 << std::endl;
	std::cout << "Count Total_2: " << total_2.count() << std::endl << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "FINE TEST FILTER_OUT VOCI" << std::endl;
	std::cout << "TUTTI I TESTI SONO STATI SUPERATI" << std::endl << std::endl << std::endl;
}

int main(){
    test_int();
    test_filter_out_int();
    
    test_string();
    test_filter_out_string();

    test_voce();
    test_filter_out_voce();
    
    return 0;
}
