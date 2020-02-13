#pragma once

#include <unordered_map>

// Maps single resource to a unordered_map, so we can keep only one copy of a resource for every instance that needs it
// instead of having multiple copies. Resources are put to the folder Resources, and into smalled dirs
// Textures for textures, Fonts for fonts, and SFX for sounds
template<typename ResourceType>
	class ResourceManager {
	private:
		std::unordered_map<std::string, ResourceType> m_Resources;
		std::string m_Folder;
		std::string m_Ext;

		std::string GetFullPath(const std::string& _name) {
			return m_Folder + _name + m_Ext;
		}

	public:
		ResourceManager(const std::string& _folder, const std::string& _ext)
			: m_Folder("Resources/" + _folder + "/"), m_Ext("." + _ext) { }

		void AddResource(const std::string& _name) {
			ResourceType res;

			res.loadFromFile(GetFullPath(_name));
			m_Resources.insert(std::make_pair(_name, res));
		}

		ResourceType& Get(const std::string& _name) {
			return m_Resources.at(_name);
		}
};