// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  size_t *count;


 public:
  /* Constructor: SmartPointer(Type* resource=NULL)
   * Uso: SmartPointer<string> myPtr(new string);
   *      SmartPointer<string> myPtr;
   * ------------------------------------------------------------
   * Construye un nuevo objeto SmartPointer que administra el recurso
   * asignado. Se asume que el recurso viene de una llamada a new.
   * El recurso también podría ser NULL lo que ocasionaría que el
   * recurso no administre ningún recurso.
   */
  explicit SmartPointer(Type *resource) :resource_(resource) {
    count = new size_t(1);
  }

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer() {
    if (count) {
      (*count)--;
      if (*count == 0) {
        delete resource_;
        delete count;
      }
    }
  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { 
      return *resource_;    
      //return Type(0); 
  }
  Type *operator->() const {
    return resource_;
      //return nullptr;
  }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other) {
    if (this != &other) {
      if (count) {
        (*count)--;
        if (*count == 0) {
          delete resource_;
          delete count;
        }
      }
      this->count = other.count;
      (*count)++;
      this->resource_ = other.resource_;
    }

    return *this;
  }
  SmartPointer &operator=(Type *other) {

    if (count) {
      (*count)--;
      if (*count == 0) {
        delete resource_;
        delete count;
      }
    }
    
    count = new size_t(1);
    this->resource_ = other;
    
    return *this;
  }
  SmartPointer(const SmartPointer &other) {
    
      if (other.count) {
        this->count = other.count;
        this->resource_ = other.resource_;
        (*count)++;
      } else {
        this->count = nullptr;
        this->resource_ = nullptr;
      }   
      
      
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const {

    return resource_;
  }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const {
    return *count;
  }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
    if (this->count) {
      (*count)--;
      if (*count == 0) {
        delete resource_;
        delete count;
      }
    }
    this->resource_ = nullptr;
    this->count = nullptr;
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
