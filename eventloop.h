#if 0
INDI
Copyright (C) 2003 Elwood C. Downey
2022 Ludovic Pollet

This library is free software;
you can redistribute it and / or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation;
either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY;
without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library;
if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301  USA

#endif

#pragma once

/** \file eventloop.h
    \brief Public interface to INDI's eventloop mechanism.
    \author Elwood C. Downey
*/

/* signature of a callback, workproc and timer function */

/** \typedef CBF
    \brief Signature of a callback function.
*/
typedef void(CBF)(int fd, void *);

/** \typedef WPF
    \brief Signature of a work procedure function.
*/
typedef void(WPF)(void *);

/** \typedef TCF
    \brief Signature of a timer function.
*/
typedef void(TCF)(void *);

#ifdef __cplusplus
extern "C" {
#endif

/** \fn void eventLoop()
    \brief Main calls this when ready to hand over control.
*/
extern void eventLoop();

/** Register a new callback, \e fp, to be called with \e ud as argument when \e fd is ready.
*
* \param fd file descriptor.
* \param fp a pointer to the callback function.
* \param ud a pointer to be passed to the callback function when called.
* \return a unique callback id for use with rmCallback().
*/
extern int addCallback(int fd, CBF *fp, void *ud);

/** Remove a callback function.
*
* \param cid the callback ID returned from addCallback().
*/
extern void rmCallback(int cid);

/** Add a new work procedure, fp, to be called with ud when nothing else to do.
*
* \param fp a pointer to the work procedure callback function.
* \param ud a pointer to be passed to the callback function when called.
* \return a unique id for use with rmWorkProc().
*/
extern int addWorkProc(WPF *fp, void *ud);

/** Remove the work procedure with the given \e id, as returned from addWorkProc().
*
* \param wid the work procedure callback ID returned from addWorkProc().
*/
extern void rmWorkProc(int wid);

/** Register a new single-shot timer function, \e fp, to be called with \e ud as argument after \e ms.
*
* \param ms timer period in milliseconds.
* \param fp a pointer to the callback function.
* \param ud a pointer to be passed to the callback function when called.
* \return a unique id for use with rmTimer().
*/
extern int addTimer(int ms, TCF *fp, void *ud);

/** Register a new periodic timer function, \e fp, to be called with \e ud as argument after \e ms.
*
* \param ms timer period in milliseconds.
* \param fp a pointer to the callback function.
* \param ud a pointer to be passed to the callback function when called.
* \return a unique id for use with rmTimer().
*/
extern int addPeriodicTimer(int ms, TCF *fp, void *ud);

/** Returns the timer's remaining value in milliseconds left until the timeout.
 *
 * \param tid the timer callback ID returned from addTimer() or addPeriodicTimer()
 * \return  If the timer not exists, the returned value will be -1.
 */
extern int remainingTimer(int tid);

/** Returns the timer's remaining value in nanoseconds left until the timeout.
 *
 * \param tid the timer callback ID returned from addTimer() or addPeriodicTimer()
 * \return  If the timer not exists, the returned value will be -1.
 */
extern int nsecRemainingTimer(int tid);

/** Remove the timer with the given \e id, as returned from addTimer() or addPeriodicTimer().
*
* \param tid the timer callback ID returned from addTimer() or addPeriodicTimer().
*/
extern void rmTimer(int tid);

/** Register a given function to be called once after the current loop
 * \param fp a pointer to the callback function.
 * \param ud a pointer to be passed to the callback function when called.
 */
extern void addImmediateWork(TCF * fp, void *ud);

/* utility functions */
extern int deferLoop(int maxms, int *flagp);
extern int deferLoop0(int maxms, int *flagp);

#ifdef __cplusplus
}
#endif
