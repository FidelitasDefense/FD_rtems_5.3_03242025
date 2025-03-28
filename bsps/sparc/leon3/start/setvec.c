/**  
 * @file
 * @ingroup RTEMSBSPsSPARCLEON3
 * @brief Install an interrupt vector on SPARC
 */

/*  This routine installs an interrupt vector on the SPARC simulator.
 *
 *  INPUT PARAMETERS:
 *    handler - interrupt handler entry point
 *    vector  - vector number
 *    type    - 0 indicates raw hardware connect
 *              1 indicates RTEMS interrupt connect
 *
 *  OUTPUT PARAMETERS:  NONE
 *
 *  RETURNS:
 *    address of previous interrupt handler
 */ 

/*  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 *
 *  Ported to LEON implementation of the SPARC by On-Line Applications
 *  Research Corporation (OAR) under contract to the European Space
 *  Agency (ESA).
 *
 *  LEON modifications of respective RTEMS file: COPYRIGHT (c) 1995.
 *  European Space Agency.
 */

#include <bsp.h>
#include <leon.h>

rtems_isr_entry set_vector(                   /* returns old vector */
  rtems_isr_entry     handler,                /* isr routine        */
  rtems_vector_number vector,                 /* vector number      */
  int                 type                    /* RTEMS or RAW intr  */
)
{
  rtems_isr_entry previous_isr;

  if ( type )
    rtems_interrupt_catch( handler, vector, &previous_isr );
  else
    _CPU_ISR_install_raw_handler( vector, (void *)handler, (void *)&previous_isr );

  if ( SPARC_IS_INTERRUPT_TRAP( vector ) ) {
    uint32_t source;

    source = SPARC_INTERRUPT_TRAP_TO_SOURCE( vector );

    LEON_Clear_interrupt( source );
    LEON_Unmask_interrupt( source );
  }

  return previous_isr;
}
