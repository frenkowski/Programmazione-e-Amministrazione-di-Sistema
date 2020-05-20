#ifndef SET_H
#define SET_H

#include <algorithm>	// std::swap
#include <ostream>		// std::ostream

#include <iterator>		// std::forward_iterator_tag
#include <cstddef>		// std::ptrdiff_t

/**
@brief add_exception

Struct che rappresenta un'eccezione. 
Viene lanciata quando si tenta di inserire un elemento che già esiste nel set.
**/
struct add_exception : public std::exception { 
	const char* what() const throw() {
		return "EXCEPTION! Element already exist in set!";
	}
};

/**
@brief remove_exception

Struct che rappresenta un'eccezione. 
Viene lanciata quando si tenta di rimuovere un elemento che non esiste nel set.
**/
struct remove_exception : public std::exception { 
	const char* what() const throw() {
		return "EXCEPTION! Element not exist in set!";
	}
};

/**
@brief index_exception

Struct che rappresenta un'eccezione. 
Viene lanciata quando si tenta di accedere ad un elemento del set tramite un indice 
che non è coerente con il numero di elementi attualmente presenti nel set. 
**/
struct index_exception : public std::exception { 
	const char* what() const throw() {
		return "EXCEPTION! Index is not coherent with the number of elements in set!";
	}
};

/**
@file set.h 
@brief Implementazione della classe set
**/

/**
@brief Set dinamico di elementi generici

Classe che rappresenta un set dinamico di elementi generici. 
Un set è una collezione di dati che non può contenere duplicati.
**/
template<typename T, typename Eql>
class set {
	struct nodo {
		T value;	///< Valore dell'elemento del set 
		nodo *next;	///< Puntatore al successivo elemento del set 

		/**
			@brief Costruttore di default 

			Costruttore di default per istanziare un nodo vuoto. 
		**/	
		nodo() : next(0) { }

		/**
		@brief Costruttore secondario

		Permette di creare un nodo a partire da un valore.

		@param v Valore dell'elemento del set
		@param n Puntatore al successivo elemento del set 
	**/
		nodo(const T &v, nodo *n=0) : value(v), next(n) { }
	};
	
	nodo *_head;			///< Puntatore al primo elemento del set 
	unsigned int _count;	///< Numero di elementi attualmente presenti nel set

	Eql _equal;				///< Funtore operatore di uguaglianza 

public:
	/**
		@brief Costruttore di default 

		Costruttore di default per istanziare un set vuoto. 
	**/	
	set() : _head(0), _count(0) { }

	/**
		@brief Copy constructor 

		Costruttore di copia 
		Permette di istanziare un set con i valori presi da un altro set.
		@param other set da usare per creare quello corrente
	**/
	set(const set &other) : _head(0), _count(0) {
		nodo *tmp = other._head;

		try {
			while(tmp!=0) {
				add(tmp->value);
				tmp = tmp->next;
			}
		}
		catch(...) {
			clear();
			throw;		
		}
	}

	/**
		@brief Numero di elementi presenti nel set 

		Ritorna il numero di elementi presenti nel set.
		@return Il numero di elementi presenti nel set
	**/
	unsigned int count() const {
		return _count;
	}

	/**
		@brief Operatore di assegnamento 

		Operatore di assegnamento 
		Permette la copia tra set.
		@param other set sorgente
		@return Riferimento a this
	**/
	set &operator=(const set &other) {
		if(&other!=this) {
			set tmp(other);
			std::swap(tmp._head, _head);
			std::swap(tmp._count, _count);
		}
		return *this;
	}

	/**
		@brief Accesso ai dati in lettura 

		Metodo per leggere il valore index-esimo del set. 

		@pre E' necessario che index < count
		@param index Indice dell'elemento del set da leggere
		@return Il valore dell'index-esimo elemento del set
	**/
	const T &operator[](unsigned int index) const {
		if(index>=_count)
			throw index_exception();
		
		nodo *tmp = _head;

		while(tmp != 0 && index-- > 0) {
			tmp = tmp->next;
		}
		return tmp->value;
	}

	/**
		@brief Distruttore

		Distruttore 
		Rimuove la memoria allocata dal set.
	**/
	~set() {
	 	clear();
	}

	/**
		@brief Clear

		Rimuove gli elementi presenti nel set. 
	**/
	void clear() {
		nodo *tmp = _head;
	 	
	 	while(tmp!=0) {
	 		nodo *next = tmp->next;
	 		delete tmp;
	 		tmp = next;
	 	}
	 	_count = 0;
	}

	/**
		@brief Aggiunta di un elemento 

		Metodo per aggiungere un elemento al set. 

		@pre E' necessario che l'elemento non sia già presente
		@param value Valore dell'elemento da aggiungere nel set 
	**/
	void add(const T &value) {
		if(find(value))	// se l'elemento è già presente lancio l'eccezione
			throw add_exception();

		nodo *n = new nodo(value);

		if(_head==0) {	// aggiunta di un elemento in un set vuoto
			_head = n;
			_count = 1;
			return;
		}

		nodo *tmp = _head, *prev = _head;

	    while(tmp!=0) {	// aggiunta in coda
	      prev = tmp;
	      tmp = tmp->next;
	    } 

	    prev->next = n;
	    n->next = tmp;
	    _count++;
	}

	/**
		@brief Rimozione di un elemento 

		Metodo per rimuovere un elemento dal set. 

		@pre E' necessario che l'elemento sia presente
		@param value Valore dell'elemento da rimuovere dal set 
	**/
	void remove(const T &value) {
		if(!find(value))
			throw remove_exception();
		
		nodo *tmp = _head;
		
		if(tmp->next == 0) {	// lista composta da un unico elemento 
			delete tmp;			// so che l'elemento è presente perchè altrimenti sarebbe stata lanciata l'eccezione
			_head = 0;
			_count = 0;
			return;
		}
		
		nodo *prev = _head;

		if(_equal(tmp->value, value) && tmp==prev) {	// rimuovo l'elemento in prima posizione, cambia _head
			_head = tmp->next;
			delete tmp;
			_count--;
			return;
		}
		
		while(tmp!=0) {
			if(_equal(tmp->value, value)) {
				prev->next = tmp->next;
				delete tmp;
				_count--;
				return;
			}
			else
				prev = tmp;
      			tmp = tmp->next;
      	}
	}

	/**
		@brief Ricerca di un elemento 

		Metodo per ricercare un elemento nel set. 

		@param value Valore dell'elemento da ricercare dal set 
		@return True se l'elemento è presente nel set, False altrimenti
	**/
	bool find(const T &value) const {
		nodo *tmp = _head;

	    while(tmp != 0 && !_equal(tmp->value, value)) {
	      tmp = tmp->next;
	    }
	    return(tmp!=0);
	}

	/**
		@brief Costruttore secondario

		Permette di creare un set a partire da una sequenza di dati 
		definita da una coppia generica di iteratori. 

		@param begin Iteratore di inizio sequenza
		@param end Iteratore di fine sequenza 
	**/
	template <typename IT>
	set(IT begin, IT end) : _head(0), _count(0) {
		try {
			for(; begin!=end; ++begin) {
				add(static_cast<T>(*begin));
			}
		}
		catch(...) {
			clear();
			throw;
		}
	}


	/**
	@brief const_iterator

	Classe che rappresenta un iteratore costante per un set dinamico di elementi generici. 
	**/
	class const_iterator {
	const nodo *n;  ///< Puntatore ad un elemento 

	public:
		typedef std::forward_iterator_tag iterator_category;
	    typedef T                         value_type;
	    typedef ptrdiff_t                 difference_type;
	    typedef const T*                  pointer;
	    typedef const T&                  reference;


		/**
			@brief Costruttore di default 

			Costruttore di default per istanziare un iteratore costante. 
		**/	
	    const_iterator() : n(0) {
	    }

		/**
			@brief Copy constructor 

			Costruttore di copia 
			Permette di istanziare un iteratore costante con i valori presi da un altro iteratore costante.
			@param other Iteratore costante da usare per creare quello corrente
		**/	    
	    const_iterator(const const_iterator &other) : n(other.n) {
	    }

		/**
			@brief Operatore di assegnamento 

			Operatore di assegnamento 
			Permette la copia tra iteratori costanti.
			@param other Iteratore costante sorgente
			@return Riferimento a this
		**/
	    const_iterator& operator=(const const_iterator &other) {
	      n = other.n;
	      return *this;
	    }

		/**
			@brief Distruttore

			Distruttore 
			Rimuove la memoria allocata dall'iteratore costante.
		**/
	    ~const_iterator() {
	    }

		/**
			@brief Operatore di dereferenziamento *

			Ritorna il dato riferito dall'iteratore.

			@return Il dato riferito dall'iteratore
		**/
	    reference operator*() const {
	      return n->value;
	    }

		/**
			@brief Operatore freccia ->

			Ritorna il puntatore al dato riferito dall'iteratore.

			@return Il puntatore al dato riferito dall'iteratore
		**/
	    pointer operator->() const {
	      return &(n->value);
	    }

		/**
			@brief Operatore di iterazione post-incremento

			Operatore di iterazione post-incremento. 

			@return Il valore prima dell'incremento
		**/	    
	    const_iterator operator++(int) {
	      const_iterator tmp(*this);
	      n = n->next;
	      return tmp;
	    }

		/**
			@brief Operatore di iterazione pre-incremento

			Operatore di iterazione pre-incremento. 

			@return Il valore incrementato
		**/	
	    const_iterator& operator++() {
	      n = n->next;
	      return *this;
	    }

		/**
			@brief Operatore di uguaglianza

			Operatore di uguaglianza. 

			@return True se i due iteratori sono uguali, False altrimenti
		**/	 
	    bool operator==(const const_iterator &other) const {
	      return (n==other.n);
	    }
	    
	    /**
			@brief Operatore di diversità

			Operatore di diversità. 

			@return True se i due iteratori sono diversi, False altrimenti
		**/	 
	    bool operator!=(const const_iterator &other) const {
	      return (n!=other.n);
	    }

	private:

	    /**
			@brief Classe friend

			La classe set è stata messa friend dell'iteratore per poter
			usare il costruttore di inizializzazione.
		**/	
	    friend class set; 

	    /**
			@brief Costruttore privato

			Costruttore privato di inizializzazione usato dalla classe set. 

			@param nn Puntatore ad un elemento del set
		**/	 
	    const_iterator(const nodo *nn) : n(nn) { 
	    }
	    	    
	  }; // classe const_iterator
	  
	/**
		@brief Begin
		Ritorna l'iteratore costante di inizio del set. 
		@return L'iteratore costante di inizio
	*/
	  const_iterator begin() const {
	    return const_iterator(_head);
	  }
	  
	/**
		@brief End
		Ritorna l'iteratore constante di fine del set. 
		@return L'iteratore costante di fine
	*/
	  const_iterator end() const {
	    return const_iterator(0);
  	}

};	// classe set

/**
	@brief Operatore di stream

	Permette di spedire su uno stream di output il contenuto del set generico.

	@param os stream di output
	@param s set da utilizzare
	@return Il riferimento allo stream di output
**/
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, const set<T, E> &s) {
	typename set<T, E>::const_iterator i, ie;
	os << "{ ";
	for(i=s.begin(), ie=s.end(); i!=ie; ++i)
		os << *i << " ";
	os << "}";
	return os;
}

/**
	@brief Operatore di concatenazione

	Ritorna un set che contiene gli elementi di entrambi i due set dati in input.

	@param first Primo set dato in input
	@param second Secondo set dato in input
	@return Un set che contiene gli elementi di entrambi i due set dati in input 
**/
template <typename T, typename E>
set<T, E> operator+(const set<T, E> &first, const set<T, E> &second) {
	set<T, E> result;
    
    typename set<T, E>::const_iterator i, ie;
    try {
    	for(i=first.begin(), ie=first.end(); i!=ie; ++i)
    		result.add(*i);
    	for(i=second.begin(), ie=second.end(); i!=ie; ++i)
    		result.add(*i);
    }
    catch(...) {
    	throw;		
    }	
    return result;
}

/**
	@brief Funzione generica che filtra gli elementi con un dato predicato

	Funzione generica che ritorna un nuovo set ottenuto prendendo tutti gli elementi che non soddisfano un dato predicato.

	@param s set da filtrare
	@param funct predicato
	@return result set con gli elementi filtrati
**/
template <typename T, typename E, typename P>
set<T, E> filter_out(const set<T, E> &s, P funct) {
	set<T, E> result;

	typename set<T, E>::const_iterator i, ie;
	try {
		for(i=s.begin(), ie=s.end(); i!=ie; ++i) {
			if(!funct(*i)) 
				result.add(*i);
		}
	}
	catch(...) {
		throw;		
	}
	return result;
}

#endif
