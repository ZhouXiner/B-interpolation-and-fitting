add_library(B_Spline SHARED
        render.cpp
        dataset.cpp
        )

target_link_libraries(B_Spline
        ${THIRD_PARTY_LIBS})