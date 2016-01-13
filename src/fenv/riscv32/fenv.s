.global feclearexcept
.type feclearexcept, %function
feclearexcept:
        csrc fflags, a0
        li a0, 0
        ret

.global feraiseexcept
.type feraiseexcept, %function
feraiseexcept:
        csrs fflags, a0
        li a0, 0
        ret

.global fetestexcept
.type fetestexcept, %function
fetestexcept:
        frflags t0
        and a0, t0, a0
        ret

.global fegetround
.type fegetround, %function
fegetround:
        frrm a0
        ret

.global __fesetround
.type __fesetround, %function
__fesetround:
        fsrm t0, a0
        li a0, 0
        ret

.global fegetenv
.type fegetenv, %function
fegetenv:
        frcsr t0
        sw t0, 0(a0)
        li a0, 0
        ret

.global fesetenv
.type fesetenv, %function
fesetenv:
        lw t1, 0(a0)
        fscsr t0, t1
        li a0, 0
        ret
