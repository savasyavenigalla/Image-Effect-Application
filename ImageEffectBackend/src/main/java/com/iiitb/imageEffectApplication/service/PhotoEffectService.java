package com.iiitb.imageEffectApplication.service;

import com.iiitb.imageEffectApplication.effectImplementation.*;
import com.iiitb.imageEffectApplication.effectImplementation.ContrastEffect;
import com.iiitb.imageEffectApplication.effectImplementation.GrayscaleEffect;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import com.iiitb.imageEffectApplication.utils.ProcessingUtils;
import libraryInterfaces.ContrastInterface;
import libraryInterfaces.GrayscaleInterface;
import libraryInterfaces.Pixel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;
import java.io.IOException;

@Service
public class PhotoEffectService {

    @Autowired
    private ProcessingUtils processingUtils;

    @Autowired
    private LoggingService loggingService;

    public ResponseEntity<byte[]> applyHueSaturationEffect(float hueAmount, float saturationAmount, MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();


            // ACTUAL WORK STARTS HERE
            HueSaturationEffect hueSat= new HueSaturationEffect();
            hueSat.setParameter("Hue", hueAmount);
            hueSat.setParameter("Saturation", saturationAmount);
            Pixel[][] modifiedImage = hueSat.apply(inputImage, imageName, loggingService);
            // TODO
           // Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE


            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }catch (IllegalParameterException e) {
            throw new RuntimeException(e);
        }
    }

    public ResponseEntity<byte[]> applyBrightnessEffect(float amount, MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();

            BrightnessEffect  effect = new BrightnessEffect();
            try {
                effect.setParameterValue(amount);
            }
            catch(IllegalParameterException e){
            }
            Pixel[][] modifiedImage = effect.apply(inputImage, imageName, loggingService);

            // ACTUAL WORK STARTS HERE

            // TODO
           // Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE



            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    public ResponseEntity<byte[]> applyContrastEffect(float amount, MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();



            // ACTUAL WORK STARTS HERE

            // TODO
            ContrastEffect effect=new ContrastEffect();
            effect.setParameterValue(amount);
            Pixel[][] modifiedImage=effect.apply(inputImage,imageName,loggingService);
            loggingService.addLog(imageName,"Contrast",String.format("%.2f",amount));
            //Pixel[][] modifiedImage = ContrastInterface.applyContrast(inputImage,amount); // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE



            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
        catch(IllegalParameterException e){
            throw new RuntimeException(e);
        }
    }

    public ResponseEntity<byte[]> applyFlipEffect(MultipartFile imageFile, int horizontalFlipValue, int verticalFlipValue) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();


            Flipimp fimp=new Flipimp();
            fimp.selectOptionValue("Horizontal",horizontalFlipValue);
            fimp.selectOptionValue("Vertical",verticalFlipValue);
            Pixel[][] modifiedImage =fimp.apply(inputImage,imageName,loggingService);
            // ACTUAL WORK STARTS HERE

            // TODO
           // Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE




            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        } catch (IllegalParameterException e) {
            throw new RuntimeException(e);
        }
    }

    public ResponseEntity<byte[]> applyGaussianBlurEffect(float radius, MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();


            // ACTUAL WORK STARTS HERE
            GaussianBlurEffect effect = new GaussianBlurEffect();
            try {
                effect.setParameterValue(radius);
            }
            catch(IllegalParameterException e){
            }
            Pixel[][] modifiedImage = effect.apply(inputImage, imageName, loggingService);
            // TODO
          //  Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE



            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    public ResponseEntity<byte[]> applyGrayscaleEffect(MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();
            loggingService.addLog(imageName,"Grayscale","");

            // ACTUAL WORK STARTS HERE
            // TODO
            GrayscaleEffect effect=new GrayscaleEffect();
            Pixel[][] modifiedImage=effect.apply(inputImage, imageName,loggingService);

            //Pixel[][] modifiedImage = GrayscaleInterface.applyGrayscale(inputImage); // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE

            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    public ResponseEntity<byte[]> applyInvertEffect(MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();

            // ACTUAL WORK STARTS HERE
            Invertimp iimp=new Invertimp();
            Pixel[][] modifiedImage = iimp.apply(inputImage,imageName,loggingService);
            // TODO
           // Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE

            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    public ResponseEntity<byte[]> applyRotationEffect(int value, MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();


            // ACTUAL WORK STARTS HERE

            // TODO
            RotationEffect effect=new RotationEffect();
            if(value==1)
            effect.selectOptionValue("90",1);
            else if(value==2)
            effect.selectOptionValue("180",2);
            else if(value==3)
            effect.selectOptionValue("270",3);
            else if(value==0)
            effect.selectOptionValue("0",0);
            Pixel[][] modifiedImage=effect.apply(inputImage,imageName,loggingService);
            //Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE


            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        } catch (IllegalParameterException e) {
            throw new RuntimeException(e);
        }
    }

    public ResponseEntity<byte[]> applySepiaEffect(MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();

            // ACTUAL WORK STARTS HERE
            SepiaEffect effect=new SepiaEffect();
            Pixel[][] modifiedImage=effect.apply(inputImage, imageName,loggingService);
            // TODO
          //  Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE

            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    public ResponseEntity<byte[]> applySharpenEffect(float amount, MultipartFile imageFile) {
        try {
            Pixel[][] inputImage = processingUtils.preprocessing(imageFile);
            String imageName = imageFile.getOriginalFilename();

            // ACTUAL WORK STARTS HERE
            SharpenEffect sharpen = new SharpenEffect();
            sharpen.setParameterValue(amount);
            Pixel[][] modifiedImage = sharpen.apply(inputImage, imageName, loggingService);
            // TODO
            //Pixel[][] modifiedImage = inputImage; // Replace this with actual modified image

            // ACTUAL WORK ENDS HERE

            return processingUtils.postProcessing(modifiedImage);

        } catch (IOException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        } catch (IllegalParameterException e) {
            throw new RuntimeException(e);
        }
    }
}
