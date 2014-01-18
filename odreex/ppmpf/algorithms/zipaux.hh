/* --
 * Copyright (C) 2014, George Makrydakis <irrequietus@gmail.com>
 *
 * This file is part of odreex.
 *
 * odreex is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * odreex is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * odreex. If not, see http://www.gnu.org/licenses/.
 *
 */

#ifndef _ODREEX_PPMPF_ALGORITHMS_ZIPAUX_HH_
#define _ODREEX_PPMPF_ALGORITHMS_ZIPAUX_HH_

#ifndef _ODREEX_PPMPF_ALGORITHMS_FOLD_HH_
#error ppmpf: <odreex/ppmpf/algorithms/zip.hh> must precede.
#endif

#define PPMPF_ZIPT_GET(x)  PPMPF_FLDX14(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_3GET(x) PPMPF_FLDX15(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_4GET(x) PPMPF_FLDX16(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_5GET(x) PPMPF_FLDX17(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_6GET(x) PPMPF_FLDX18(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_7GET(x) PPMPF_FLDX19(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_8GET(x) PPMPF_FLDX1A(PPMPF_FLDX0P,x)
#define PPMPF_ZIPT_9GET(x) PPMPF_FLDX1B(PPMPF_FLDX0P,x)

#define PPMPF_ZIPT_POP(x)  PPMPF_FLDX14(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_3POP(x) PPMPF_FLDX15(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_4POP(x) PPMPF_FLDX16(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_5POP(x) PPMPF_FLDX17(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_6POP(x) PPMPF_FLDX18(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_7POP(x) PPMPF_FLDX19(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_8POP(x) PPMPF_FLDX1A(PPMPF_FLDX0Q,x)
#define PPMPF_ZIPT_9POP(x) PPMPF_FLDX1B(PPMPF_FLDX0Q,x)

#define PPMPF_ZIPT_EMPTY(x)  PPMPF_FLDX1C(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_3EMPTY(x) PPMPF_FLDX1D(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_4EMPTY(x) PPMPF_FLDX1E(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_5EMPTY(x) PPMPF_FLDX1F(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_6EMPTY(x) PPMPF_FLDX1G(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_7EMPTY(x) PPMPF_FLDX1H(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_8EMPTY(x) PPMPF_FLDX1I(PPMPF_OR,PPMPF_FLDX0R,x)
#define PPMPF_ZIPT_9EMPTY(x) PPMPF_FLDX1J(PPMPF_OR,PPMPF_FLDX0R,x)

#define PPMPF_ZIPT_APPLY(f,sl,g,...) \
        ((PPMPF_APPLY(f,PPMPF_DREF(g(PPMPF_DREF(PPMPF_SEQ_POP(sl)))))))
        
#endif /* _ODREEX_PPMPF_ALGORITHMS_ZIPAUX_HH_ */
