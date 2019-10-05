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

	static std::string ToString(Suit suit) {
		switch (suit) {
		case Suit::Hearts:
			return "Hearts";
		case Suit::Diamonds:
			return "Diamonds";
		case Suit::Clubs:
			return "Clubs";
		case Suit::Spades:
			return "Spades";
		default:
			return "";
		}
	}

	template <typename T>
	class Iterator {
	public:
		virtual ~Iterator() = default;
		virtual bool HasNext() const = 0;
		virtual void Next() = 0;
		virtual T* const Current() const = 0;
		virtual void Reset() = 0;
	};

	template <typename T>
	class Collection {
	public:
		virtual ~Collection() = default;
		virtual std::unique_ptr<Iterator<T>> GetIterator() const = 0;
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

	class Hand : public Collection<Card> {
	public:
		virtual ~Hand() = default;
		void AddCard(std::unique_ptr<Card> card);
		Card* const ViewCard(unsigned index) const;
		std::unique_ptr<Card> RemoveCard(unsigned index);
		unsigned GetHandSize() const;
		virtual std::unique_ptr<Iterator<Card>> GetIterator() const override;
	private:
		std::vector<std::unique_ptr<Card>> cards_;
	};

	class CardIterator : public Iterator<Card> {
	public:
		CardIterator(Hand const* hand) :
			hand_(hand),
			index_(0) {};
		virtual ~CardIterator() = default;
		virtual bool HasNext() const override {
			return (index_ < (hand_->GetHandSize() - 1));
		}
		virtual void Next() override {
			++index_;
		}
		virtual Card* const Current() const override {
			return hand_->ViewCard(index_);
		}
		virtual void Reset() override {
			index_ = 0;
		}
	private:
		Hand const* hand_;
		unsigned index_;
	};

	void Hand::AddCard(std::unique_ptr<Card> card) {
		cards_.push_back(std::move(card));
	}
	Card* const Hand::ViewCard(unsigned index) const {
		return cards_.at(index).get();
	}
	std::unique_ptr<Card> Hand::RemoveCard(unsigned index) {
		return std::move(cards_.at(index));
	}
	unsigned Hand::GetHandSize() const {
		return cards_.size();
	}
	std::unique_ptr<Iterator<Card>> Hand::GetIterator() const {
		return std::make_unique<CardIterator>(this);
	};

	void Run() {
		Hand hand;
		std::cout << "Adding some cards to the hand." << std::endl;
		hand.AddCard(std::make_unique<Card>(Suit::Hearts, 5));
		hand.AddCard(std::make_unique<Card>(Suit::Clubs, 2));
		hand.AddCard(std::make_unique<Card>(Suit::Spades, 12));
		hand.AddCard(std::make_unique<Card>(Suit::Diamonds, 10));
		hand.AddCard(std::make_unique<Card>(Suit::Clubs, 6));
		hand.AddCard(std::make_unique<Card>(Suit::Spades, 8));

		std::cout << "Cards:" << std::endl;
		auto it = hand.GetIterator();
		while (it->HasNext()) {
			auto card = it->Current();
			std::cout << card->Value << " of " << ToString(card->Suit) << std::endl;
			it->Next();
		}
	}
}