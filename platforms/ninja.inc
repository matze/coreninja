FILE %(|PATH)build.ninja

PRINTNL cc = %(CC)
PRINTNL cflags = %(CFLAGS)
PRINTNL cxx = %(CXX)
PRINTNL cxxflags = %(CXXFLAGS)
PRINTNL ldflags = %(LDFLAGS)
PRINTNL ar = %(AR)
PRINTNL
PRINTNL rule cxx
PRINTNL   depfile = $out.d
PRINTNL   command = $cxx -MD -MF $out.d $cxxflags -c $in -o $out
PRINTNL
PRINTNL rule link_binary
PRINTNL   command = $cxx $in -o $out $ldflags
PRINTNL
PRINTNL rule link_shared_object
PRINTNL   command = $cxx -shared $in -o $out $ldflags
PRINTNL
PRINTNL rule ar
PRINTNL   command = $ar rcs $out $in
PRINTNL

FOR EACH CON
    FOR EACH SOURCE
        PRINTNL build %(OUTPUTPATH)%(NAME).o: cxx %(NAME)

        // Adapt cxxflags for include paths
        PRINT   cxxflags = $cxxflags

        FOR EACH ../USE
            FOR EACH INCLUDE
                PRINT  -I%(NAME)
            ENDFOR
        ENDFOR
        PRINTNL
    ENDFOR

    PRINTNL

    PRINT build %(OUTPUTPATH)%(NAME): link_binary

    // Link object files
    FOR EACH SOURCE
        PRINT   %(OUTPUTPATH)%(NAME).o
    ENDFOR

    // Link static libs
    FOR EACH USE
        IF (%(TYPE) == "lib")
            PRINT   %(OUTPUTPATH)lib%(NAME).a
        ENDIF
    ENDFOR

    PRINTNL

    // Link shared libs
    PRINT   ldflags = $ldflags

    FOR EACH USE
        IF (%(TYPE) == "dll")
            PRINT   %(OUTPUTPATH)lib%(NAME).so
        ENDIF
    ENDFOR

    PRINTNL
ENDFOR

PRINTNL

FOR EACH LIB
    FOR EACH SOURCE
        PRINTNL build %(OUTPUTPATH)%(NAME).o: cxx %(NAME)
        PRINT   cxxflags = $cxxflags
        FOR EACH ../INCLUDE
          PRINT  -I%(NAME)
        ENDFOR
        PRINTNL
    ENDFOR

    PRINTNL

    PRINT build %(OUTPUTPATH)lib%(NAME).a: ar

    FOR EACH SOURCE
        PRINT   %(OUTPUTPATH)%(NAME).o
    ENDFOR

    PRINTNL
ENDFOR

PRINTNL

FOR EACH DLL
    FOR EACH SOURCE
        PRINTNL build %(OUTPUTPATH)%(NAME).o: cxx %(NAME)
        PRINT   cxxflags = $cxxflags
        FOR EACH ../INCLUDE
          PRINT  -I%(NAME)
        ENDFOR
        PRINTNL
    ENDFOR

    PRINTNL

    PRINT build %(OUTPUTPATH)lib%(NAME).so: link_shared_object

    FOR EACH SOURCE
        PRINT   %(OUTPUTPATH)%(NAME).o
    ENDFOR

    PRINTNL
FOR EACH
