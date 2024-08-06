## About the project:
The project is about making an image effect software which applies image effects such as - hue-saturation, contrast, brightness, flip, gaussian blur, grayscale, invert, rotation, sepia, sharpen.

## Purpose:
Through this project we can implement image effects by creating .cpp files for the effects and also java wrapper to call the cpp function for each effect. We are also using a user friendly Angular frontend to interact with image effects. We also handled some exceptions such as Illegal parameter exception. Along with effects we have also made a logging service which creates logs for each effect operation and store them in a file.

## Executing the project:
1.Setting up the Frontend
	- Go to project directory and run “npm i”.
	- Go to the ImageEffectFrontEnd directory inside the project folder and run “npm i”.
	- Run “npm start” inside the ImageEffectFrontEnd directory.
	- Check the localhost url/port and open it in a browser.
2.Setting up the Backend
	- Go to the ImageEffectBackEnd directory inside the project folder and run “make clean” and “make”.
	- Load the dependencies in pom.xml
	- Right click on [ImageEffectApplicatio.java] and run file.

## ImageEffects (.cpp codes)

1. Hue-Saturation:
**`applyHueSaturation`** modifies an image's colors by adjusting its hue and saturation. It converts pixels from RGB to HSV color space, adjusts hue by **`hueValue`** (0-360 degrees), and modifies saturation based on **`saturationValue`** (-100 to 100). It then converts the adjusted HSV values back to RGB and ensures the pixel RGB values are within the valid range (0-255).

2. Brightness:
 **`apply_brightness_cpp`** adjusts an image's overall brightness by uniformly altering each pixel's RGB values. It modifies the red, green, and blue channels by a specified **`amount`** (adjusted by subtracting 50 from the input value) within a range of 0 to 100. The function ensures the resulting RGB values remain within the valid range of 0 to 255 for each channel, effectively brightening or darkening the entire image uniformly.

3. Contrast:
The **`apply_contrast_cpp`** calculates the minimum and maximum intensity values in the image, then adjusts the contrast using a formula that involves modifying the intensity values for each pixel individually. The adjustment is based on the provided **`amount`** parameter, which alters the contrast via a formula dependent on the pixel intensity values. The clamping ensures the modified intensity values stay within the valid range of 0 to 255 for each RGB channel. Overall, this function enhances or reduces the contrast of the image based on the **`amount`** parameter provided.

4. Flip:
**`apply_flip_cpp`** flips an image horizontally if **`hz`** is set to 1 and vertically if **`v`** is set to 1. It achieves this by reversing either individual rows (for horizontal flip) or the entire vector of rows (for vertical flip) using **`reverse`**. The function alters the arrangement of pixels, producing a flipped version of the image based on the specified flags (**`hz`** and **`v`**).

5. Gaussian Blur:
 **`apply_gaussianblur_cpp`**  starts by determining the necessary parameters for the Gaussian blur process, such as the **`sigma`** value derived from the input **`radius`**. It generates a square kernel matrix based on this radius to define the weights for blurring. The kernel is calculated using the Gaussian distribution formula to assign weights to the neighboring pixels of each image pixel.

Once the kernel is generated, the function normalizes its values by dividing each element by the total sum of all elements within the kernel. This normalization ensures that the weighted average computed later does not distort the image brightness.
The blur effect is applied to the image by iterating through its pixels, excluding the border pixels determined by the radius. For each pixel in the image, the function calculates the weighted sum of the surrounding pixel values based on the Gaussian kernel. This weighted sum effectively produces the blurred value for the current pixel in the temporary image container (**`tempImage`**).

Finally, the function updates the original image (**`imageVector`**) with the blurred pixel values stored in **`tempImage`**, resulting in the application of Gaussian blur to the entire image based on the specified **`radius`**. The process smoothens the transitions between neighboring pixels, reducing image noise and enhancing visual aesthetics through a blurred effect.

6. Grayscale:
 **`applyGrayscale`** involves traversing through each pixel and calculating its grayscale intensity using a weighted combination of the pixel's RGB values. This weighted average formula incorporates specific coefficients (0.2989 for red, 0.587 for green, and 0.114 for blue) to determine the grayscale intensity. the function ensures the computed intensity remains within the acceptable range of grayscale values (0-255). The function updates the original image by replacing each pixel's RGB values with the newly calculated grayscale values.

7. Invert:
**`apply_invert_cpp`** achieves image inversion by iterating through each pixel in the 2D vector of pixels (**`imageVector`**) and flipping their RGB values to their complementary values by subtracting each channel's current value from 255 (the maximum value for an 8-bit channel). This process creates a negative image effect by inverting the colors across the entire image.

8. Rotation:
The **`rotate90`** function performs a 90-degree counterclockwise rotation by creating a new matrix, **`rotatedImage`**, and rearranging the pixels by interchanging rows and columns. The **`apply_rotation`** function interprets the input **`value`** to determine the desired rotation angle: for **`value`** equals 1, it executes a 90-degree rotation using **`rotate90`**, for **`value`** equals 2, it applies a 180-degree rotation by calling **`rotate90`** twice, and for **`value`** equals 3, it rotates the image by 270 degrees by invoking **`rotate90`** three times. These functions provide the ability to flexibly adjust image orientation in multiples of 90 degrees counterclockwise, catering to diverse rotation requirements within the image processing workflow.

9. Sepia:
**`applySepia`** processes an image represented as a 2D vector of pixels (**`image`**) to impart a sepia tone effect. It accomplishes this by iterating through each pixel in the image and calculating new RGB values based on a predefined formula for sepia conversion. This formula involves weighted combinations of the original RGB components to produce sepia-toned equivalents. After computing these new values, the function ensures they fall within the acceptable range of RGB values (0-255) and updates the image's pixels accordingly. The resulting output is an image transformed to evoke the warm, nostalgic tones characteristic of sepia photography, achieved through the adjustment of individual pixel colors based on the specified sepia transformation algorithm.

10. Sharpen:
**`applySharpen`** sharpens an image represented by a 2D vector of pixels (**`imageVector`**). It enhances image details and edges by intensifying the contrast between pixels using a sharpening algorithm (kernel matrix). The **`amount`** parameter regulates the strength of the sharpening effect. The function iterates through the image pixels, excluding borders, adjusting the RGB values based on a specific formula to create a sharper image.

## effectImplementation (.java codes)

1. Hue-Saturation 
The Java class **`HueSaturationEffect`** implements the **`ParameterizableEffect`** interface, intended for applying hue and saturation adjustments to an image. It maintains private attributes **`hueValue`** and **`saturationValue`** to store the parameters for hue and saturation adjustments. The **`apply`** method utilizes the **`HueSaturationInterface`** to apply the hue and saturation effect on the input **`image`**, generating a modified image. Additionally, it logs the application of the effect by recording the effect name, along with the specific hue and saturation values, using a **`LoggingService`**. The **`setParameter`** method validates and sets the **`hueValue`** and **`saturationValue`** based on the provided parameters. If the provided parameter name matches "Hue" or "Saturation" and the value is within the valid range (0 to 100), it sets the corresponding attribute; otherwise, it throws an **`IllegalParameterException`**.

2. Invert, Sepia, Grayscale:
The Java class **`Invertimp`** implements the **`PhotoEffect`** interface and is intended to apply the inversion effect to an image. It contains an **`apply`** method that takes in a 2D array of pixels (**`image`**), applies the inversion effect using the **`InvertInterface`**, and returns the modified image. The **`InvertInterface`** likely contains the implementation for inverting the pixel colors. This class is designed to be used within an image effect application framework, where **`fileName`** represents the name of the image file and **`lservice`** is a **`LoggingService`** used for logging purposes within the application. Overall, the **`Invertimp`** class encapsulates the functionality to perform an image inversion effect within the image processing application framework.

Similarly apply the java implementation for Grayscale and Sepia.

3. Flip, Rotation:
The Java class **`Flipimp`** implements the **`DiscreteEffect`** interface and is designed to perform flipping operations on images. It maintains private attributes **`hzflipval`** and **`vertflipval`**, initialized to 0, which represent the flip options for horizontal and vertical flipping, respectively. The class contains an **`apply`** method that takes in a 2D array of pixels (**`image`**), along with a **`fileName`** representing the image file's name, and a **`LoggingService`** (**`lservice`**). It applies the flipping effect using the **`FlipInterface`** by passing the image and flip options, then returns the modified image.
Additionally, the **`selectOptionValue`** method allows setting flip options based on **`optname`** (either "Horizontal" or "Vertical") and the associated **`v`** value. If the option name matches "Horizontal" or "Vertical," it updates the corresponding flip value (**`hzflipval`** or **`vertflipval`**). Otherwise, it throws an **`IllegalParameterException`**. Overall, the **`Flipimp`** class encapsulates functionalities to perform horizontal or vertical flipping operations within an image processing application framework.

Similarly apply the java implementation for Rotation.

4. Sharpen, Gaussian Blur, Contrast, Brightness
The **`BrightnessEffect`** Java class implements the **`SingleValueParameterizableEffect`** interface to adjust image brightness. It maintains the **`amountValue`** attribute representing the brightness adjustment magnitude. The **`apply`** method utilizes **`BrightnessInterface`** to apply the brightness adjustment to the image based on **`amountValue`**. The **`setParameterValue`** method sets **`amountValue`** after validating the input within the range of -200 to 200, throwing an **`IllegalParameterException`** otherwise. This class manages image brightness modifications within an image processing application framework.

Similarly apply the java implementation for Gaussian Blur, Contrast, Sharpen.

## LoggingService:
1. **Service Annotation**: The **`@Service`** annotation indicates that this class is a Spring service component and can be automatically detected and configured by Spring's component scanning.
2. **Fields**:
    - **`THREAD_POOL_SIZE`**: Defines the number of threads in the thread pool used for asynchronous logging.
    - **`threadPool`**: An **`ExecutorService`** responsible for managing the thread pool for asynchronous logging.
    - **`LOG_FILE_PATH`**: Specifies the path for the log file.
    - **`logs`**: A **`List`** storing **`LogModel`** objects to retain log entries in memory.
3. **Constructor**:
    - **`LoggingService()`**: Initializes the **`threadPool`** by creating a fixed-size thread pool with **`THREAD_POOL_SIZE`**. Additionally, it loads existing logs from the log file and populates the **`logs`** list during object instantiation.
4. **Methods**:
    - **`addLog(String fileName, String effectName, String optionValues)`**: Asynchronously adds a log entry to the log file and updates the in-memory log list.
    - **`writeToLogFile(String fileName, String effectName, String optionValues)`**: Writes a log entry to the log file and adds it to the in-memory log list.
    - **`getAllLogs()`**: Retrieves all log entries from the in-memory log list.
    - **`getLogsByEffect(String effectName)`**: Retrieves log entries for a specific image effect from the in-memory log list.
    - **`clearLogs()`**: Clears all log entries from both the in-memory log list and the log file.
    - **`getLogsBetweenTimestamps(LocalDateTime startTime, LocalDateTime endTime)`**: Retrieves log entries within a specified time range from the in-memory log list.
    - **`loadLogs()`**: Loads existing log entries from the log file during initialization and populates the in-memory log list.
5. **Additional Method**:
    - **`shutdownThreadPool()`**: Shuts down the thread pool when it's no longer needed.


			
