#pragma once


namespace TinyEngine {

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};

}

namespace std {

	template <typename T> struct hash;

	template<>
	struct hash<TinyEngine::UUID>
	{
		std::size_t operator()(const TinyEngine::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}