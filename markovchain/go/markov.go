package main

import(
	"fmt"
	"strings"
)


type Token struct {
	Token string
	Count int
}

type TokenList []Token

//Checks if a Token already exists in a TokenList
func (tkl *TokenList) contains(word string) (exists bool, position int) {
	exists = false
	position = -1
	for index, token := range *tkl {
		if token.Token == word {
			exists = true
			position = index
			return
		}
	}
	return
}

//The Markov Chain
type Chain struct {
	Tokens map[string] TokenList
}

/*The Create method generates a new Chain
For each token it registers the tokens and count that come
after it
*/
func (c *Chain) Create(sentence string) {
	splitSentence := strings.Split(sentence," ")
	sentenceLen := len(splitSentence)
	c.Tokens = make(map[string]TokenList, sentenceLen)

	for index, word := range splitSentence {
		if index == 0 {
			c.Tokens[" "] = TokenList{Token{Token: word, Count:1}}
			c.Tokens[word] = TokenList{Token{Token: splitSentence[1], Count:1}}
		} else if index == sentenceLen - 1 {
			if c.Tokens[word] == nil {
				c.Tokens[word] = TokenList{Token{Token: " ", Count: 1}}
			} else {
				c.Tokens[word] = append(c.Tokens[word], Token{Token: " ", Count: 1})
			}
		} else {
			if c.Tokens[word] == nil {
				c.Tokens[word] = TokenList{Token{Token: splitSentence[index + 1], Count:1}}
			} else {
				tokenList := c.Tokens[word]
				if exists, position := tokenList.contains(splitSentence[index + 1]); exists {
					tokenList[position].Count++
				} else {
					c.Tokens[word] = append(c.Tokens[word], Token{Token:splitSentence[index + 1], Count: 1})
				}
			}
		}
	}
}

// The most probable next word will be the word that came the most after a given token
// It's calculated by dividing the number of times a given token appeared by the 
// Total number of tokens that appeared after that token
func (c *Chain) MostProbableNextWord(word string) (nextWord string, probability float64) {
	wordProbabilities  := make(map[string]float64, len(c.Tokens[word]))
	tokenListLen := 0
	for _,token := range c.Tokens[word] {
		tokenListLen += token.Count
	}
	for _,token := range c.Tokens[word] {
		wordProbabilities[token.Token] = float64(token.Count) / float64(tokenListLen)
	}

	for w, p := range wordProbabilities {
		if p > probability {
			probability = p
			nextWord = w
		}
	}
	return
}

//Simple example
func main() {
	myChain := new(Chain)
	myChain.Create("my test my test my cat cat cat")
	fmt.Println(myChain.Tokens)
	w, p := myChain.MostProbableNextWord("my")
	fmt.Printf("%s, %f\n", w, p)
	w, p = myChain.MostProbableNextWord("cat")
	fmt.Printf("%s, %f\n", w, p)
}
