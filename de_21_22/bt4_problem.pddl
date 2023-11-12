(define (problem cargos_problem) 
    (:domain cargos_domain)
    (:objects 
        P1 P2 P3 TSN NB PL
    )

    (:init
        (Package P1)
        (Package P2)
        (Package P3)
        (Airport TSN)
        (Airport NB)
        (Plane PL)
        (At P1 TSN)
        (At P2 TSN)
        (At P3 NB)
        (At PL TSN)
    )

    (:goal 
        (and
            (At P1 NB)
            (At P2 NB)
            (At P3 TSN)
        )
    )


)
