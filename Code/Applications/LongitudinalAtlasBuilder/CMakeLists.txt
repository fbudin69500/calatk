#
# Add the Atlas Builder application
#
set(libraries ${FFTW_LIB} ${ITK_LIBRARIES})
add_clp_application(LongitudinalAtlasBuilder LongitudinalAtlasBuilder ${libraries})
