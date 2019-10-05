#include <iostream>
#include <exception>
#include <vector>

namespace Iterator {
	class InvalidValueException : public std::exception {};

	enum class Suit {
		Hearts,
		Diamonds,
		Clubs,
		Spades
	};

	template <typename T>
	class Iterator {
	public:
		virtual ~Iterator() = default;
		virtual bool HasNext() const = 0;
		virtual void Next() = 0;
		virtual T const* Current() const = 0;
	};

	template <typename T>
	class Collection {
	public:
		virtual ~Collection() = default;
		virtual const std::unique_ptr<Iterator<T>> GetIterator() const = 0;
	};

	struct Card {
		Card(Suit suit, unsigned val) :
			Suit(suit),
			Value(val)
		{
			if ((Value < 2) || (Value > 14))
				throw InvalidValueException();
		}
		const Suit Suit;
		const unsigned Value;
	};

	// Forward declaration of hand for the iterator
	class Hand;

	class CardIterator : public Iterator<Card> {
	public:
		CardIterator(Hand const* hand) :
			hand_(hand) {};
		virtual ~CardIterator() = default;
		virtual Card const* Current() const {
		}
	private:
		Hand const* hand_;
	};

	class Hand : public Collection<Card> {
	public:
		void AddCard(std::unique_ptr<Card> card) {
			cards_.push_back(std::move(card));
		}
		virtual const std::unique_ptr<Iterator<Card>> GetIterator() const {
			return std::make_unique<CardIterator>(this);
		};
	private:
		std::vector<std::unique_ptr<Card>> cards_;
	};

	void Run() {
		Hand hand;
	}
}