:- dynamic([estacionado/2]).

frases_poner --> [estaciona];[lleva].
frases_sacar --> [saca];[trae].
objeto --> [auto];[vehiculo].

estaciona(P,L) :- 	estacionado(P,_) ->
						(fail);estacionado(_,L) ->
							(fail);assert(estacionado(P,L)).
							
estaciona_algo --> [P],[en],[L],[y],estaciona_algo,{estaciona(P,L)}.							
estaciona_algo --> [P],[en],[L],{estaciona(P,L)}.
							
accion_estacionar -->	frases_poner,
						objeto,
						estaciona_algo.

accion_sacar -->	frases_sacar,objeto,[P],
					{
						estacionado(P,_) ->
							retract(estacionado(P,_));(fail)
					}.

accion --> accion_estacionar;accion_sacar.

oracion --> accion.