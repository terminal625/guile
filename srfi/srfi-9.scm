;;;; srfi-9.scm --- SRFI-9 procedures for Guile
;;;;
;;;; 	Copyright (C) 2001 Free Software Foundation, Inc.
;;;; 
;;;; This program is free software; you can redistribute it and/or
;;;; modify it under the terms of the GNU General Public License as
;;;; published by the Free Software Foundation; either version 2, or
;;;; (at your option) any later version.
;;;; 
;;;; This program is distributed in the hope that it will be useful,
;;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;;;; General Public License for more details.
;;;; 
;;;; You should have received a copy of the GNU General Public License
;;;; along with this software; see the file COPYING.  If not, write to
;;;; the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
;;;; Boston, MA 02111-1307 USA

;;; This module exports the syntactic form `define-record-type', which
;;; is the means for creating record types defined in SRFI-9.
;;;
;;; The syntax of a record type definition is:
;;;
;;;  <record type definition>
;;;    -> (define-record-type <type name>
;;;         (<constructor name> <field tag> ...)
;;;         <predicate name>
;;;         <field spec> ...)
;;;
;;;  <field spec> -> (<field tag> <accessor name>)
;;;               -> (<field tag> <accessor name> <modifier name>)
;;;
;;;  <field tag> -> <identifier>
;;;  <... name>  -> <identifier>
;;;
;;; Usage example:
;;;
;;; guile> (use-modules (srfi srfi-9))
;;; guile> (define-record-type :foo (make-foo x) foo? 
;;;                            (x get-x) (y get-y set-y!))
;;; guile> (define f (make-foo 1))
;;; guile> f
;;; #<:foo x: 1 y: #f>
;;; guile> (get-x f)
;;; 1
;;; guile> (set-y! f 2)
;;; 2
;;; guile> (get-y f)
;;; 2
;;; guile> f
;;; #<:foo x: 1 y: 2>
;;; guile> (foo? f)
;;; #t
;;; guile> (foo? 1)
;;; #f

(define-module (srfi srfi-9))

(export-syntax define-record-type)

(define-macro (define-record-type type-name constructor/field-tag
		predicate-name . field-specs)
  `(begin
     (define ,type-name
       (make-record-type ',type-name ',(map car field-specs)))
     (define ,(car constructor/field-tag)
       (record-constructor ,type-name ',(cdr constructor/field-tag)))
     (define ,predicate-name
       (record-predicate ,type-name))
     ,@(map
	(lambda (spec)
	  (cond
	   ((= (length spec) 2)
	    `(define ,(cadr spec)
	       (record-accessor ,type-name ',(car spec))))
	   ((= (length spec) 3)
	    `(begin
	       (define ,(cadr spec)
		 (record-accessor ,type-name ',(car spec)))
	       (define ,(caddr spec)
		 (record-modifier ,type-name ',(car spec)))))
	   (else
	    (error "invalid field spec " spec))))
	field-specs)))
