(define (domain cargos_domain)

    (:requirements :strips)


    (:predicates 
        (In ?obj ?place)
        (At ?obj ?place)
        (Package ?obj)
        (Plane ?obj)
        (Airport ?obj)
    )


    (:action LOAD
        :parameters (?cargo ?plane ?airport)
        :precondition (and 
            (At ?cargo ?airport)
            (At ?plane ?airport)
            (Package ?cargo)
            (Plane ?plane)
            (Airport ?airport)
        )
        :effect (and 
            (not (At ?cargo ?airport))
            (In ?cargo ?plane)
        )
    )

    (:action UNLOAD
        :parameters (?cargo ?plane ?airport)
        :precondition (and 
            (In ?cargo ?plane)
            (At ?plane ?airport)
            (Package ?cargo)
            (Plane ?plane)
            (Airport ?airport)
        )
        :effect (and 
            (not (In ?cargo ?plane))
            (At ?cargo ?airport)
        )
    )

    (:action FLY
        :parameters (?plane ?from ?to)
        :precondition (and 
            (At ?plane ?from)
            (Plane ?plane)
            (Airport ?from)
            (Airport ?to)
        )
        :effect (and         
            (not (At ?plane ?from))
            (At ?plane ?to)
        )
    )
)