#include "../hdr/image.hpp"

namespace engine {
	sf::Image image;
	std::vector<std::string> imageNames;
	int imageIndex = 0;
	std::string imageName;
	bool imageLoaded = false; 

	void loadImage(const std::string& fileName) {
		imageLoaded = image.loadFromFile(fileName); 
	}
	gs::Color getPixel(gs::Vec2f position, gs::Vec2i resolution) {
		const gs::Vec2u imageSize = image.getSize(); 
		const gs::Vec2f positionScaler = gs::Vec2f(
			static_cast<float>(imageSize.x) / static_cast<float>(resolution.x),
			static_cast<float>(imageSize.y) / static_cast<float>(resolution.y)
		);
	
		// Stretches image to match the given resolution. 
		return image.getPixel(
			std::floor(position.x * positionScaler.x),
			std::floor(position.y * positionScaler.y)
		); 
	}
	void updateImageFileDirectory() {
		const std::string path = "Images/"; 
		const std::string validExtensions[] = 
			{ ".png", ".jpg", ".jpeg", ".bmp", ".jfif"};
		
		imageNames.clear(); 
		
		for (const auto& fileEntry : 
				std::filesystem::directory_iterator(path)) {
			const std::string& filePathName = fileEntry.path().string(); 
			const int dotIndex = filePathName.find_last_of('.'); 
			
			// Only continues validation if a file format is detected. 
			if (dotIndex != -1) {
				// Gets the file extension from the filename. 
				const std::string fileExtension = filePathName.substr(dotIndex);

				for (const std::string& extension : validExtensions) {
					// Only add image files with a valid file extension. 
					if (extension == fileExtension)
						imageNames.push_back(filePathName); 
				}
			}
		}
	}
	void gotoNextImage() {
		// Moves to the next image and resets the index if it's too large. 
		imageIndex++; 
		if (imageNames.size() != 0)
			imageIndex %= imageNames.size(); 

		if (imageIndex < imageNames.size()) {
			imageName = imageNames[imageIndex]; 
			loadImage(imageName); 
			// Removes the directory that the image comes from. 
			imageName = imageName.substr(imageName.find_last_of('/') + 1); 
		}
	} 
	void takeScreenshot() {
		auto generateScreenshotName = [](int fileIndex) -> std::string {
			return "Screenshots/screenshot" + std::to_string(fileIndex) 
				+ ".png";
		};

		const sf::Image screenshot =  
			render::imageRenderingArea.getTexture().copyToImage(); 
		
		int fileIndex = 0; 

		// Keeps increasing the fileIndex until a valid index is found. 
		while (std::filesystem::exists(generateScreenshotName(fileIndex)))
			fileIndex++; 

		screenshot.saveToFile(generateScreenshotName(fileIndex)); 
	}
}