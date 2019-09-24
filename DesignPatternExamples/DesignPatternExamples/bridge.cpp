#include <iostream>
#include <string>
#include <vector>

namespace Bridge {
	class Resource {
	public:
		std::string Name() { return name_; }
		std::string Description() { return desc_; }
		unsigned Size() { return size_; }
		std::string Path() { return path_; }

	protected:
		Resource(std::string name, std::string desc, unsigned size, std::string path) :
			name_(name), desc_(desc), size_(size), path_(path) {};

		std::string name_ = "";
		std::string desc_ = "";
		unsigned size_ = 0;
		std::string path_ = "";
	};

	class AudioResource : public Resource {
	public:
		AudioResource(std::string name, std::string desc, unsigned size, std::string path, std::string album) :
			Resource(name, desc, size, path), album_(album) {};
		std::string Album() { return album_; }

	private:
		std::string album_ = "";
	};

	class VideoResource : public Resource {
	public:
		VideoResource(std::string name, std::string desc, unsigned size, std::string path, bool isHD) :
			Resource(name, desc, size, path), hd_(isHD) {};
		bool HD() { return hd_; }

	private:
		bool hd_;
	};

	class View {
	public:
		void AddResource(Resource& resource) {
			resources_.push_back(std::reference_wrapper<Resource>(resource));
		}
		virtual void Show() = 0;

	protected:
		View() = default;

		std::vector<std::reference_wrapper<Resource>> resources_;
	};

	class FullView : public View {
	public:
		virtual void Show() override {
			for (Resource& resource : resources_) {
				std::cout << resource.Name()
					<< " | " << resource.Description()
					<< " | " << resource.Path()
					<< " | " << resource.Size()
					<< std::endl;
			}
		}
	};

	class PathView : public View {
	public:
		virtual void Show() override {
			for (Resource& resource : resources_) {
				std::cout << resource.Path() << std::endl;
			}
		}
	};

	void Run() {
		AudioResource song1("Sudden Sky", "Crown the Empire", 15386, "C:\\Music\\suddensky.mp3", "Single");
		AudioResource song2("Nihilist Blues", "Annaisokay", 12342, "C:\\Music\\nihilistblues.mp3", "Nihilist Blues");
		VideoResource video1("Sinister", "Best horror movie of all time. Fight me.", 6894738, "C:\\Movies\\Horror\\sinister.avi", true);

		FullView full;
		PathView path;

		full.AddResource(song1);
		full.AddResource(song2);
		full.AddResource(video1);

		path.AddResource(song1);
		path.AddResource(song2);
		path.AddResource(video1);

		std::cout << "Full view:" << std::endl;
		full.Show();
		std::cout << std::endl << "Path view:" << std::endl;
		path.Show();
	}
}