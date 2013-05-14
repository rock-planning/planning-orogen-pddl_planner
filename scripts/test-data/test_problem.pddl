(define (problem test_domain-1)
(:domain test_domain)
(:objects
        sherpa_0 - physob_id
	crex_0 - physob_id
	pl_0 - physob_id
	sherpa - physob_type
	location_s0 - location
	location_c0 - location
	location_p0 - location
)
(:init 
        (is_a sherpa_0 sherpa)
	(is_a crex_0 crex)
	(is_a pl_0 payload)
	(at sherpa_0 location_s0)
	(at crex_0 location_c0)
	(at pl_0 location_p0)
	(can_move sherpa_0)
	(can_move crex_0)
)
(:goal (at sherpa_0 location_c0)
)
)

