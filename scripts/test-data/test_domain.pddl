(define (domain test_domain)
    (:requirements :strips :equality :typing :conditional-effects)
    (:types location physob_id physob_type)
    (:constants sherpa crex payload - physob_type)
    (:predicates ( at ?x - physob_id ?l - location)
                 ( is_a ?x - physob_id ?r - physob_type)
                 ( connected ?x ?y - physob_id)
		 ( cannot_move ?x - physob_id)
    )

; General effects
; moving physically bounded objects affect position for all
(:action move
    :parameters (?obj - physob_id ?m ?l - location)
    :precondition ( and (at ?obj ?m) (not (= ?m ?l)) (not (cannot_move ?obj) ))
    :effect (and (at ?obj ?l) (not (at ?obj ?m))
             (forall (?z)
	             (when (and (connected ?z ?obj) (not (= ?z ?obj)))
		           (and (at ?z ?l) (not (at ?z ?m)))
			  )))
)

; Moving into the range, means that both systems
; meet a certain location
; Not predicate need to be reset (in effect otherwise, doubling of
; predicate is possible, e.g. (at s 1) (at s 1) which should not hold
; since a physical object cannot be in two locations at the same time
(:action move_into_range
    :parameters (?x ?y - physob_id ?m ?l - location)
    :precondition (and (not (cannot_move ?x)) (at ?x ?m) (at ?y ?l) )
    :effect (and (at ?x ?l) (at ?y ?l) (not (at ?x ?m)))
)

; Connecting two systems requires them to be at the same position
(:action connect
    :parameters (?x ?y - physob_id ?l - location)
    :precondition (and (at ?x ?l) (at ?y ?l))
    :effect (and (connected ?x ?y) (cannot_move ?y))
)

; Disconnecting two object
(:action disconnect
    :parameters (?x ?y - physob_id)
    :precondition (and (not (= ?x ?y)) (connected ?x ?y)) 
    :effect (and (not (connected ?x ?y)) (not (cannot_move ?y)))
)

; END DOMAIN
)

