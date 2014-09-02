#ifndef HOSPITAL_SIMPLE_HPP_
#define HOSPITAL_SIMPLE_HPP_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/dist/lognormaldist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include <eosim/statics/timeseries.hpp>
#include "paciente.hpp"
#include "entidad.h"

/*
Este es el modelo de simulacion del ejemplo del hospital simple presentado en el libro
Simulation Modelling with Pascal - Ruth Davies, Robert O'Keefe

Este modelo esta construido en 2 fases
*/

class HospitalSimple: public eosim::core::Model {
private:
	// tasa de arribos de los pacientes
	double tasaArribos;
	// tiempo de estadia de los pacientes
	double tiempoEstadia;
	// evento de arribo de los pacientes y alimentador (fijo)
	PacienteFeeder pF;
	// evento de salida de los pacientes (fijo)
	SalidaPaciente sP;
	CrearEvento crearEvento;

public:
	// distribucion aleatoria de arribos de pacientes (exponencial)
	eosim::dist::NegexpDist arribos;
	// distribucion aleatoria de estadia de pacientes (exponencial)
	eosim::dist::LogNormalDist estadia;
	// cola de espera por camas
	eosim::utils::EntityQueueFifo cola;
	// camas del hospital
	eosim::core::Renewable camas;
	// acumulador de datos sobre los tiempos de espera en las colas
	eosim::statics::TimeSeries colaEnTiempo;
	// acumulador de datos sobre los tiempos de espera en las colas
	eosim::statics::Observation tEspera;
	// acumulador de datos sobre el largo medio de la cola
	eosim::statics::TimeWeighted lCola;
	// Indice para saber con qué media está ejecutando y el runIn correspondiente
	int indiceMedia;
	// booleano para saber si no estoy en el Steady State
	bool notSteadyState;
	// constructor del modelo
	HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia, int indiceMedia);
	// destructor del modelo
	~HospitalSimple();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};

#endif

