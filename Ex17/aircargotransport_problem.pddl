(define (problem pb1)
    (:domain air-cargo)
    (:objects C1 C2 P1 P2 SFO JFK)
    (:init
        ;; type
        (Cargo C1)
        (Cargo C2)
        (Plane P1)
        (Plane P2)
        (Airport SFO)
        (Airport JFK)
        ;; location
        (At C1 SFO)
        (At C2 JFK)
        (At P1 SFO)
        (At P2 JFK)
    )
    (:goal(and  (At C1 JFK)
                (At C2 SFO)))
)