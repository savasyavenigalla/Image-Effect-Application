package com.iiitb.imageEffectApplication.effectImplementation;
import com.iiitb.imageEffectApplication.baseEffects.DiscreteEffect;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.FlipInterface;
import libraryInterfaces.Pixel;
//import com.iiitb.imageEffectApplication.libraryInterfaces.Pixel;
//import com.iiitb.imageEffectApplication.libraryInterfaces.FlipInterface;

// Class declaration for the Flipimp class implementing the DiscreteEffect interface
public class Flipimp implements DiscreteEffect
{
    private int hzflipval=0, vertflipval=0; // 0 for no flip, 1 for flip according to the option
    // Method to apply the flip effect on the image
    public Pixel[][] apply(Pixel [][] image, String fileName, LoggingService loggingService)
    {
        String effectName = "Flip";
        String optionValues = String.format("Horizontal flip: %d, Vertical Flip: %d",  hzflipval,  vertflipval);
        loggingService.addLog(fileName, effectName, optionValues); // Adding log entry for the applied flip effect
        return FlipInterface.applyFlip(image,hzflipval,vertflipval);
    }

    // Method to select the flip option value
    public void selectOptionValue(String optname,int v) throws IllegalParameterException
    {
        // Checking the provided option name and setting the corresponding flip value
        if(optname.equals("Horizontal"))
        {
            hzflipval=v;
        }
        else if (optname.equals("Vertical"))
        {
            vertflipval=v;
        }
        else {
            throw new IllegalParameterException(); // Throwing an exception for illegal parameter values
        }
    }
}