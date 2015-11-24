#ifndef ARREGLO_DIMENSIONABLE_H
#define ARREGLO_DIMENSIONABLE_H

#include <iostream>

using namespace std;

template<typename DataType>
class ArregloDimensionable {
	public:
		ArregloDimensionable();												// constructor por defecto
		ArregloDimensionable( int tamanio );								// constructor con paŕmetros
		ArregloDimensionable( const ArregloDimensionable<DataType>& otroArreglo );	// constructor por copia
		~ArregloDimensionable();// destructor por defecto

		ArregloDimensionable<DataType> crearArregloDimensionableVacio(int tamanio);
		bool esArregloDeNULL();

		void insertarAtras( DataType elem);
		int tamanio() const;
		const DataType& iesimo( int i ) const;
		DataType& iesimo( int i );
		
		ArregloDimensionable<DataType>& operator=( const ArregloDimensionable<DataType>& otroArreglo );
		bool operator==( const ArregloDimensionable<DataType>& otroArreglo ) const;
		
		template<typename Data> friend
            ostream& operator<<( ostream& flujo, const ArregloDimensionable<Data>& otroArreglo );
        
	private:
		DataType* _arreglo;
		int  _espacio;  
		int  _ultimo;
};


// IMPLEMENTACION


template<typename DataType>
ArregloDimensionable<DataType>::ArregloDimensionable(){
	_espacio = 1;		
	_ultimo  = 0;
	_arreglo = new DataType[_espacio];
}

template<typename DataType>
ArregloDimensionable<DataType>::ArregloDimensionable( int tamanio ){
	_espacio = tamanio;		
	_ultimo  = 0;
	_arreglo = new DataType[_espacio];
}


template<typename DataType>
ArregloDimensionable<DataType>::ArregloDimensionable( const ArregloDimensionable<DataType>& otroArreglo ){
	// al tener bien definido el "operator=", puedo hacer esto directamente:
	this->_arreglo = NULL;
	*this = otroArreglo;
}

template<typename DataType>
ArregloDimensionable<DataType>::~ArregloDimensionable(){
	//cout << "--> Se llama el Destructor por defecto para: " << "(" << this << ") = "<< *this << endl;	
	delete[] _arreglo;
}

template<typename DataType>
void ArregloDimensionable<DataType>::insertarAtras( DataType elem ){
	if( _ultimo == _espacio ) {				// NO TENGO MAS MEMORIA PARA AGREGAR...
		DataType* arregloViejo = _arreglo;	// me hago un backup del arreglo anterior
		_arreglo = new DataType[_espacio*2];// redimensiono el arreglo, pide el doble de memoria que tenia
		for( int i = 0; i < _espacio; ++i )	// copia el arreglo anterior en el nuevo redimensionado...
			_arreglo[i] = arregloViejo[i];
		_espacio *= 2;						// actualizo el valor del tamanio
		delete arregloViejo;				// borro de la memoria el arreglo anterior...
	}
	_arreglo[_ultimo] = elem;				// agrego el elemento
	_ultimo++;								// actualizo el ultimo agregado
}

template<typename DataType>
int ArregloDimensionable<DataType>::tamanio() const {
	return _ultimo;
}

template<typename DataType>
const DataType& ArregloDimensionable<DataType>::iesimo( int i ) const {
	return _arreglo[i];	
}

template<typename DataType>
DataType& ArregloDimensionable<DataType>::iesimo( int i ) {
	return _arreglo[i];	
}


template<typename DataType>
ArregloDimensionable<DataType>& ArregloDimensionable<DataType>::operator=( const ArregloDimensionable<DataType>& otroArreglo ){
	// Hay que copiar el otroArreglo, es decir, pedir memoria y copiar cada elemento nuevo en memoria...  
	if( this != &otroArreglo ){									// esto nos salva si se hiciera "x = x;"
		delete this->_arreglo;									// libero la memoria anterior
		this->_espacio = otroArreglo.tamanio();					// actualizo valores
		this->_ultimo  = 0; 									// actualizo valores
		this->_arreglo = new DataType[_espacio]; 					// pido memoria según el tamanio del nuevo arreglo...
		for( int i = 0; i < otroArreglo.tamanio(); i++ )		// copio los elemento de a uno...
			this->insertarAtras( otroArreglo._arreglo[i] );
	}
	return *this;
}

template<typename DataType>
bool ArregloDimensionable<DataType>::operator==( const ArregloDimensionable<DataType>& otroArreglo ) const{
	if( this->tamanio() != otroArreglo.tamanio() )
		return false;
	int i = 0;
	while( i < _ultimo && _arreglo[i] == otroArreglo._arreglo[i] )
		i++;
	return (i == _ultimo);
}

template<typename DataType>
ostream& operator<<( ostream& flujo, const ArregloDimensionable<DataType>& otroArreglo ){
	flujo << "[";
	for( int i = 0; i < otroArreglo._ultimo; i++ ){
		flujo << otroArreglo._arreglo[i];
		if( i != otroArreglo._ultimo-1 )
			flujo << ",";
	}
	flujo << "]";
	return flujo;
}

template <typename DataType>
ArregloDimensionable<DataType> ArregloDimensionable<DataType>::crearArregloDimensionableVacio(int tamanio){
	this->_espacio = tamanio;
	this->_arreglo = new DataType[_espacio];
	int i;
	for (i = 0; i < tamanio; i++)
	{
		this->_arreglo[i] = NULL;
	}
	this->_ultimo = 0;
	return *this;
}

template <typename DataType>
bool ArregloDimensionable<DataType>::esArregloDeNULL(){
	int i;
	int j = 0;
	for (i = 0; i < this->_espacio; i++)
	{
		if (this->_arreglo[i] == NULL) j++;
	}
	return j == this->_espacio-1;
}
#endif // ARREGLO_DIMENSIONABLE_H
