package model

import "backend/lib/db"

type (
	EnvConfig struct {
		Host  string
		Port  int
		Mongo db.MongoConfig
	}
)
