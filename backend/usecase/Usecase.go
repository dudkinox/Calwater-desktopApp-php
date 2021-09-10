package usecase

import (
	"context"
)

type CrudUseCaseI interface {
	GetHealthCheck(ctx context.Context) (err error)
}
