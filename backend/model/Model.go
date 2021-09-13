package model

import "go.mongodb.org/mongo-driver/bson/primitive"

type (
	GetNameResponse struct {
		Data []ModelSave `json:"table"`
	}
	ModelSave struct {
		Id   primitive.ObjectID `json:"_id,omitempty" bson:"_id,omitempty" validate:"required"`
		Name string             `json:"Name"`
	}
)
