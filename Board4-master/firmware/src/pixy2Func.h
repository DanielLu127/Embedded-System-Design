/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _PIXY_FUNCS    /* Guard against multiple inclusion */
#define _PIXY_FUNCS


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "pixy_queue.h"
#include "debug.h"
#include "system_definitions.h"

#define TooLong 65
/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
#define midpoint 158
   typedef enum {sample} PixyStandAlone;
   typedef enum {None , Red, Green} RType; // keeps track of what color it's looking at
   
   extern void fetchBlocks(uint8_t numSigMaps, uint8_t maxBlocks );
   
   void setXs(uint8_t datum, unsigned int counter, uint32_t * x_arr); // this function handles the x array
   
   void setYs(uint8_t datum ,unsigned int counter, uint32_t * y_arr); // this function handles the y array
   
   void setSigMap(uint8_t datum , unsigned int counter, uint32_t * sig_map); // this function handles the signature map
   
   void setAngles(uint8_t datum , unsigned int counter, int * angles); // stores angles
   void setWidth(uint8_t datum , unsigned int counter, uint32_t * wide); // stores width
   
    void strAssgn(unsigned char * msg, unsigned char *buf,  unsigned int len);
   
   //datum is the character, counter is what byte this is, x_array is an array of x values, y_arr is an array of y values
   void queueData(uint8_t datum, unsigned int counter, uint32_t * x_arr, uint32_t * y_arr, uint32_t * sig_map, int * deg, uint32_t * wide, uint32_t * ylen  , unsigned int * numVars);
   
   void MSB(uint32_t * Data, unsigned int slot, unsigned char * msg , unsigned int location);
   
   void Midval(uint32_t * Data, unsigned int slot, unsigned char * msg, unsigned int location);
   
   void LSB(uint32_t * Data, unsigned int slot, unsigned char * msg, unsigned int location);
   
   
   void SendValsToUART(unsigned int NumberOfVariables , uint32_t * x_arr, uint32_t * y_arr, uint32_t * sig_map , uint32_t * deg, uint32_t * wide, uint32_t * ylen);
   
   void pixy_uart_fsm(void);
   
   uint16_t Pixy_look_up_init(int loc); // look up table for angles
   uint16_t Pixy_time_lut(int loc); // look up table for time
   
   int get_color_index(color_tracked val, int * sigs, int num_vars);
   
   // main pixy functions I can probably do most of what I need with only these
   void setPixy2Universal(uint8_t datum, unsigned int counter, unsigned int define,  uint32_t * buf);
   void directionPixy(uint32_t * wide, uint32_t * ylen, int * sig, uint32_t * x, uint32_t * y, unsigned int num_vars);
   void motorPixy(uint32_t * wide, uint32_t * ylen, uint32_t * sig, uint32_t * x,  uint32_t * y,  unsigned int num_vars);
  
   
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
